#pragma once
#include <iostream>
#include <vector>
#include "report.h"

using namespace std;
using v1 = vector<int>;
using v2 = vector<vector<int>>;
using v3 = vector<vector<vector<int>>>;

using v1d = vector<double>;
using v2d = vector<vector<double>>;
using v3d = vector<vector<vector<double>>>;
//template <typename rep>


class Ekv
{
private:
    vector<elData> m_grid;
    int m_ukz;

    int m_dim;
    v2d m_R;
                 v3d m_R_full;
    v1 m_numConnections;
    v1d m_U;
    //v2 m_parEl;

    v1 m_nodesIncludinonGens;
    bool m_checkInitNodesIncludinonGens;

    vector<Report> m_rep;
public:

    Ekv(vector<elData> grid, int ukz);
    //m_checkInitNodesIncludinonGens = false;
    //m_parEl = InParEl(m_grid,m_dim);

    v2d getR();
    void ekvParEl_C();//ekv parallel element
    void ekvPosEl_C();
    void ekvGen_C();
    v1 InNodesIncludinonGens_C();

    int lastEl();
    double resistEkv();
    double U_Ekv();
    double currentEkv();
    void valuesEkvOut();

    void outParEkv();
};

// нужно чтобы m_nodesIncludinonGens тоже инициализировалась, просто дл€ единообрази€
// при вызове екв ген пусть каждый раз вызвалась переделка узлѕодкл√ен

// в методе екв√ен уже в конце все мен€етс€, все дополнительные вектора