#pragma once
//#include <cstdlib>
#include "functions.h"
#include "Ekv.h"
#include "report.h"

int Report::m_countCommon = 0;


int main()
{


//Make_data
    vector<elData> grid;
    grid = { {1,2,0,1,100.0001},
             {1,2,0,2,100.0002},
             {1,2,0,6,99.999},
             {1,1,1,3,2.001},
             {1,1,2,3,4.002},
             {2,1,2,3,4.002},
             {3,1,2,3,4.002},
             {1,1,3,4,2},
             {1,1,4,5,2},
             {1,1,5,6,2} };
    int ukz = 4;
    //test
    Ekv test{ grid,ukz };
    
    while (test.lastEl() > 2)
    {
        cout << "befoere ekv par el\n" << test.getR() << "\n";
        test.ekvParEl_C();
        cout << "after ekv par el\n" << test.getR() << "\n";
        test.ekvPosEl_C();
        cout << "after ekv pos el\n" << test.getR() << "\n";
        //test.InNodesIncludinonGens_C();
        test.ekvGen_C();
        cout << "after ekv gen el\n" << test.getR() << "\n";
    }
    test.valuesEkvOut();

    test.outParEkv();


    system("pause");   
}

/* проверит работу, почеуму numConnections в 4 узле =0

переделать инициализацию на U = функция которая ретурн вектор

сделать функцию под экв генов

сделать экв /\ в звезду

подумать над матрицей как R только в которйо пишется колличетво пар ветвей

сделать enum про ветку сопр и напряжения
такжже сделать enum для выброса действия эквивалетирования: cout<<" мы экв сеть (убрали пар элемент, убрали посл элемент, экв гены)"


*/