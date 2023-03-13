#pragma once

#include <iostream>
#include <vector>
using namespace std;
using v1 = vector<int>;
using v2 = vector<vector<int>>;
using v3 = vector<vector<vector<int>>>;

using v1d = vector<double>;
using v2d = vector<vector<double>>;
using v3d = vector<vector<vector<double>>>;

ostream& operator << (ostream& os, const v2& vec);
ostream& operator << (ostream& os, const v1& vec);

ostream& operator << (ostream& os, const v2d& vec);
ostream& operator << (ostream& os, const v1d& vec);

struct elData
{
    int par;
    int type;
    int nodeSt;
    int nodeEnd;
    double value;
};

v2d initializationR(const vector<elData>& grid, int dim );

v1 InNumCon(const v2d& R, int dim);

v1d InU(const vector<elData>& grid, int dim);

int DimGrid(const vector<elData>& grid);//

double Ekv_par_el(double Y1, double Y2);

void makeR(v2d& R, const vector<elData>& grid);

void makeNodesIncludinonGens(v1& nodesIncludinonGens, const v1& numConnections, const v2& R);

v3d InR_Full(const vector<elData>& grid, int dim);///

void DelU(v2d& R, int num, v1& conn);



void makeSize(v2& vec, int dim);

void makeSize(v2d& vec, int dim);

void makeSize(v1& vec, int dim);

void makeSize(v1d& vec, int dim);