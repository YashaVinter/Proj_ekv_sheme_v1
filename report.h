#pragma once

struct EkvPar
{
    bool state;
    int nodeSt, nodeEnd;
    int numPar1, numPar2, numParAfter;
    double val_1_before, val_2_before, val_after;
};
struct EkvPos
{
    bool state;
    int nodeSt, nodeEnd;
    int numPar;
    int val_1_before, val_2_before, val_after;
};
struct EkvGen
{
    bool state;
};
struct EventData
{
    EkvPar ekvPar;
    EkvPos ekvPos;
    EkvGen ekvGen;
};
struct Report
{
    static int m_countCommon;
    int m_count;
    EventData data;

    Report();


	static void plusCount();
	void makeNote( int nSt, int nEnd, int numBranch1, int numBranch2, double valBranch1, double valBranch2, int numBranchEkv, double valBranchEkv )
	{
        m_count = m_countCommon;

        data.ekvPar.state = 1;
        data.ekvPar.nodeSt = nSt;
        data.ekvPar.nodeEnd = nEnd;

        data.ekvPar.numPar1 = numBranch1;
        data.ekvPar.numPar2 = numBranch2;
        data.ekvPar.numParAfter = numBranchEkv;

        data.ekvPar.val_1_before = valBranch1;
        data.ekvPar.val_2_before = valBranch2;
        data.ekvPar.val_after = valBranchEkv;
        plusCount();
	}

};




//Mind:
//Отчет: 2, эквивалентирование последовательное, 
//вектор стек, в нем структура, в которой вектор(инт счетчик, тип события енум, структура данные по событию)
//если мы экв пар ветви, то надо описание :
//вид события, узлел Н, узел К, валуе 1 до, валуе 2 до, валуе после

//example:
//vector<Report> report1{ 0 };
//
//report1[0].count = 1;
//report1[0].data.ekvPar.nodeEnd = 1;
