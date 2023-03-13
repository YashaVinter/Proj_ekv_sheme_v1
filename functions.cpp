#pragma once
#include "functions.h"
using v1 = vector<int>;
using v2 = vector<vector<int>>;
using v3 = vector<vector<vector<int>>>;

ostream& operator << (ostream& os, const v2& vec)
{
    for (auto& row : vec)
    {
        for (auto& col : row)
            cout << col << " ";
        cout << endl;
    }
    return os;
}
ostream& operator << (ostream& os, const v1& vec)
{
    for (auto& row : vec)
        cout << row << endl;
    return os;
}

ostream& operator << (ostream& os, const v2d& vec)
{
    for (auto& row : vec)
    {
        for (auto& col : row)
            cout << col << "\t";
        cout << endl;
    }
    return os;
}
ostream& operator << (ostream& os, const v1d& vec)
{
    for (auto& row : vec)
        cout << row << endl;
    return os;
}


 void makeR(v2d& R, const vector<elData>& grid)
 {
     for (int i = 0; i < grid.size(); i++)
     {
         if (grid[i].type == 1)
         {
             const auto& x = grid[i].nodeSt - 1;
             const auto& y = grid[i].nodeEnd - 1;
             R[x][y] = grid[i].value;
             R[y][x] = grid[i].value;
         }
     }
 }

 void makeNodesIncludinonGens(v1& nodesIncludinonGens, const v1& numConnections, const v2& R)
 {
     for (int i = 0; i < nodesIncludinonGens.size(); i++)
     {
         if (numConnections[i] == 1)
         {
             for (int j = 0, size2 = nodesIncludinonGens.size(); j < size2; j++)
             {
                 if (R[i][j] != 0)
                 {
                     nodesIncludinonGens[i] = j + 1;
                     continue;
                 }
             }
         }
     }
 }

 v2d initializationR(const vector<elData>& grid, int dim = 6)
 {
     v2d R;
     makeSize(R, dim);
     makeR(R, grid);
     return R;
 }

 v1 InNumCon(const v2d& R, int dim )
 {
     v1 numCon;
     makeSize(numCon, dim);
	 for (int i = 0; i < numCon.size(); i++)
	 {
		 for (int j = 0; j < numCon.size(); j++)
		 {
			 if ((R[i][j] != 0))
			 {
				 numCon[i]++;
			 }
		 }
	 }
     return numCon;
 }

 v1d InU(const vector<elData>& grid, int dim)
 {
	 v1d U;
     makeSize(U,dim);
	 for (int i = 0; i < grid.size(); i++)
	 {
		 if ((grid[i].type == 2))
		 {
			 U[grid[i].nodeEnd - 1] = grid[i].value;
		 }
	 }
	 return U;
 }

 v3d InR_Full(const vector<elData>& grid, int dim) 
 {
     v3d R_full;
     R_full.resize(dim);
     for (auto& row : R_full)
         row.resize(dim);
     
     //R_full[0][0].push_back(10);

     for (int i = 0; i < grid.size(); i++)
     {
         if (grid[i].type == 1)
         {
             const auto& x = grid[i].nodeSt - 1;
             const auto& y = grid[i].nodeEnd - 1;
             R_full[x][y].push_back(grid[i].value);
             R_full[y][x].push_back(grid[i].value);
         }
     }
     return R_full;
 }

 void DelU(v2d& R, int num, v1& conn)
 {
     vector <int> pos_del;
     vector <double> val_del;
     //pos_del.resize(2);
     double val_ekv = 0;


     for (int i = 0, size1 = R.size(); i < size1; i++)
     {
         for (int j = 0, size2 = R.size(); j < size2; j++)
         {
             if ((i == num) && (R[i][j] != 0))
             {
                 pos_del.push_back(j);
                 val_del.push_back(R[i][j]);
             }
             if ((i == num) || (j == num))
             {
                 R[i][j] = 0;
             }
         }
     }
     val_ekv = val_del[0] + val_del[1];
     R[pos_del[0]][pos_del[1]] = val_ekv;
     R[pos_del[1]][pos_del[0]] = val_ekv;
     // ekv  conn
     conn[num] = 0;
 }


 int DimGrid(const vector<elData>& grid)
 {
     int dim = 0;
     for (int i = 0; i < grid.size(); i++)
     {
         if (dim < grid[i].nodeEnd)
         {
             dim = grid[i].nodeEnd;
         }
     }
     return dim;
 }

 double Ekv_par_el(double Y1, double Y2)
 {
     return (Y1 * Y2 / (Y1 + Y2));
 }


 void makeSize(v2& vec, int dim)
 {
     vec.resize(dim);
     for (auto& row : vec)
         row.resize(dim);
 }
 void makeSize(v2d& vec, int dim)
 {
     vec.resize(dim);
     for (auto& row : vec)
         row.resize(dim);
 }
 void makeSize(v1d& vec, int dim)
 {
     vec.resize(dim);
 }
 void makeSize(v1& vec, int dim)
 {
     vec.resize(dim);
 }
