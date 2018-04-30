#include <QCoreApplication>
#include "ambiente.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int main(int argc, char *argv[])
{
    ofstream result;
    int popS=atoi(argv[1]);
    int popT=atoi(argv[2]); // população de tubarões
    result.open("resPops=_"+(string)argv[1]+"_PopT=_"+(string)argv[2]+"_.csv");
    result << "popS=" << popS<< "    popT="<<popT<<endl;
    result << "tempoCC;tempoSC"<<endl;

    for(int si=1;si<=10;si++)
    {
        ambiente oceanoCC(popS,popT,true); // com efeito cardume
        ambiente oceanoSC(popS,popT,false);
        int timeCC=0,timeSC=0;
        while(oceanoCC.getNAg()>popS/2)
        {
            oceanoCC.roda();
            timeCC++;
        }
        while(oceanoSC.getNAg()>popS/2)
        {
            oceanoSC.roda();
            timeSC++;
        }
        result << timeCC << ";" << timeSC << endl;
        cout << timeCC << ";" << timeSC << endl;
    }
    result.close();
}
