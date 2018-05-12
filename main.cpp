#include <QCoreApplication>
#include "ambiente.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <time.h>
#include "worker.h"

using namespace std;

int main(int argc, char *argv[])
{
    ofstream result;
    clock_t ti,tf;
    int popS=atoi(argv[1]);
    int popT=atoi(argv[2]); // população de tubarões
    result.open("resPops=_"+(string)argv[1]+"_PopT=_"+(string)argv[2]+"_.csv");
    result << "popS=" << popS<< "    popT="<<popT<<endl;
    result << "tempoCC;tempoSC"<<endl;
    ti=clock();
    for(int si=1;si<=10;si++)
    {
        ambiente oceanoCC(popS*3,popT,true); // com efeito cardume
        ambiente oceanoSC(popS,popT,false);// sem efeito
        worker ambCC(&oceanoCC);
        worker ambSC(&oceanoSC);

        ambCC.start();
        ambSC.start();

        ambCC.wait();
        cout << "esperando o SC" << endl;
        ambSC.wait();
        result << ambCC.tempo << ";" << ambSC.tempo << endl;
        cout << ambCC.tempo << ";" << ambSC.tempo << endl;
    }
    tf=clock();
    cout << "tempo:" << (double)(tf-ti)/CLOCKS_PER_SEC << endl;
    result.close();
}
