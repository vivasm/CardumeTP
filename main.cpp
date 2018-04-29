#include <QCoreApplication>
#include "ambiente.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    int popS=201;
    int popT=2; // população de tubarões

    for(int si=1;si<=10;si++)
    {
        ambiente oceano(popS,popT);
        int time=0;
        while(oceano.getNAg()>popS/2)
        {
            oceano.roda();
            //cout << oceano.getNAg() <<endl;
            time++;
        }
        cout << time <<endl;
    }
}
