#pragma once
#include "functions.h"
#include <vector>
#include "Ekv.h"

using v1 = vector<int>;
using v2 = vector<vector<int>>;
using v3 = vector<vector<vector<int>>>;



Ekv::Ekv(vector<elData> grid, int ukz) : m_grid{ grid }, m_ukz{ ukz }//construct
{ {
        m_dim = DimGrid(m_grid);
        m_R_full = InR_Full(m_grid, m_dim);
        m_R = initializationR(m_grid, m_dim);
        m_numConnections = InNumCon(m_R, m_dim);
        m_U = InU(m_grid, m_dim);

        m_nodesIncludinonGens = InNodesIncludinonGens_C();
        m_rep.resize(0);
    }}

v2d Ekv::getR()
{
    return m_R;
}

void Ekv::ekvParEl_C()
{
    for (int i = 0; i < m_R_full.size(); i++)
    {
        for (int j = 0; j < m_R_full.size(); j++)
        {
			if (m_R_full[i][j].size() > 1)
            {
				for (int k = (m_R_full[i][j].size() - 1); k > 0; k--)//reducing stack
				{
					const auto& first = m_R_full[i][j][0];
					const auto& end = m_R_full[i][j][k];
                    const auto& ekv = Ekv_par_el(first, end);
                        

                    m_rep.resize(m_rep.size() + 1);
                    m_rep[Report::m_countCommon].makeNote(i, j, 0, k, first, end, 0, ekv);

					m_R_full[i][j][0] = ekv;
                    m_R_full[i][j].pop_back();

                    //int a = Report::m_countCommon;
				}
                m_R[i][j] = m_R_full[i][j][0];// transfer to main massiv:  R
            }
        }
    }

}

void Ekv::ekvPosEl_C() 
{
    for (int i = 0; i < m_numConnections.size(); i++)
    {
		if ((m_numConnections[i] == 2) && (m_ukz != (i + 1)) && (m_U[i] == 0))
        {
            int nodeEkv = i + 1;
            cout << "ekv uzel = " << nodeEkv << endl;
            // zatiraem svyazi 5 uzla
            DelU(m_R, i, m_numConnections);


            for (int i = 0; i < m_dim; i++)
            {
                if ((nodeEkv)== m_nodesIncludinonGens[i])
                {
                    for (int j = 0; j < m_dim; j++)
                    {
                        if ((i!=j)&&(m_R[i][j]!=0))
                        {
                            m_nodesIncludinonGens[i] = j + 1;
                        }
                    }

                }
            }



        }
    }
}

void Ekv::ekvGen_C() 
{
    if (m_checkInitNodesIncludinonGens == 0) 
        InNodesIncludinonGens_C();

    bool state1;//i!=j, не экв ген сам на себя
    bool state2;//связности ветвей должны быть равны и равны 1
    bool state3;//узел подключения !=0

    for (int i = 0; i < m_nodesIncludinonGens.size(); i++)
    {
        for (int j = 0; j < m_nodesIncludinonGens.size(); j++)
        {
            state1 = (m_nodesIncludinonGens[i] == m_nodesIncludinonGens[j]) && (i != j);
            state2 = m_numConnections[i] == m_numConnections[j] == 1;
            state3 = (m_nodesIncludinonGens[i]) && (m_nodesIncludinonGens[j]);

            if (state1 && state2 && state3) // здесь ищутся все, колличество генов подкл к общ точке
            {
                // значит нужно ген i и j - эквивалентировать!

                    //экв сопр, записываем в 1 ген

                double R1 = m_R[i][m_nodesIncludinonGens[i] - 1];
                double R2 = m_R[j][m_nodesIncludinonGens[j] - 1];
                double Rekv = Ekv_par_el(R1, R2);

                //записываем Рекв в 1 элемент
                m_R[i][m_nodesIncludinonGens[i] - 1] = Rekv;
                m_R[m_nodesIncludinonGens[i] - 1][i] = Rekv;

                m_R[j][m_nodesIncludinonGens[j] - 1] = 0;
                m_R[m_nodesIncludinonGens[j] - 1][j] = 0;

                //Ekv U

                double E1 = m_U[i];
                double E2 = m_U[j];
                double Eekv = ((E1 / R1) + (E2 / R2)) * Rekv;
                m_U[i] = Eekv;
                m_U[j] = 0;

                m_nodesIncludinonGens[j] = 0;
                m_numConnections[j] = 0;
                --m_numConnections[m_nodesIncludinonGens[i] - 1];
            }
        }
    }
}

//
v1 Ekv::InNodesIncludinonGens_C()//creating new local variable  m_nodesIncludinonGens rather them var in the class
{
    //v1 m_nodesIncludinonGens;
    makeSize(m_nodesIncludinonGens, m_dim);

    for (int i = 0; i < m_nodesIncludinonGens.size(); i++)
    {
        if (m_numConnections[i] == 1)
        {
            for (int j = 0, size2 = m_nodesIncludinonGens.size(); j < size2; j++)
            {
                if (m_R[i][j] != 0)
                {
                    m_nodesIncludinonGens[i] = j + 1;
                    continue;
                }
            }
        }
    }
    m_checkInitNodesIncludinonGens = true;
    return m_nodesIncludinonGens;
}


int Ekv::lastEl()
{
    int sum{};
    for (const auto &el : m_numConnections )
    {
        sum += el;
    }
    return sum;
}
// при экв посл элементов, нужно переписать узел подключения гена, 


double Ekv::resistEkv() 
{
    for (int i = 0; i < m_R[0].size(); ++i)
    {
        for (int j = 0; j < m_R[0].size(); ++j)
        {
            if (m_R[i][j] != 0)
            {
                return m_R[i][j];
            }
        }
    }
    return -1;
}

double Ekv::U_Ekv()
{
    for (int i = 0; i < m_U.size(); ++i)
    {
        if (m_U[i] != 0)
        {
            return m_U[i];
        }
    }
    return -1;
}


double Ekv::currentEkv() 
{
	if ((U_Ekv() < 0) || (resistEkv() < 0))
    {
        cout << "Hueston, we have problems!\n";
    }
	return U_Ekv() / resistEkv();
}

void Ekv::valuesEkvOut()
{
    cout << "Congratulation! scheme was equivalenting!\n";
    cout << "Ekv resist: " <<resistEkv() << endl;
    cout << "Ekv E: " << U_Ekv() << endl;
    cout << "Ekv current: " << currentEkv() << endl;
}

void Ekv::outParEkv()
{
    cout << "\n\tEquivalenting  number: " << 1 << endl;
    cout << "Node start: " << m_rep[0].data.ekvPar.nodeSt << "\tNode end: " << m_rep[0].data.ekvPar.nodeEnd << endl;
    cout << "Number par brach 1: " << m_rep[0].data.ekvPar.numPar1 << "\tNumber par brach 2: " << m_rep[0].data.ekvPar.numPar2 << endl;
    cout << "Value par brach 1: " << m_rep[0].data.ekvPar.val_1_before << "\tValue par brach 2: " << m_rep[0].data.ekvPar.val_2_before << endl;
    cout << "Number brach after equivalenting: " << m_rep[0].data.ekvPar.numParAfter << "\tValue brach after equivalenting: " << m_rep[0].data.ekvPar.val_after << endl<<endl;
    /*Report::m_countCommon
    data.ekvPar.nodeSt*/
}