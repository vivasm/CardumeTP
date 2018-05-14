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

    double tempoCC[10], tempoSC[10];

    #pragma omp parallel for num_threads(4)
    for(int si=1;si<=10;si++)
    {
        ambiente oceanoCC(popS,popT,true); // com efeito cardume
        ambiente oceanoSC(popS,popT,false);// sem efeito
        worker ambCC(&oceanoCC);
        worker ambSC(&oceanoSC);

        ambCC.run();
        ambSC.run();

        tempoCC[si-1] = ambCC.tempo;
        tempoSC[si-1] = ambSC.tempo;

    }
    tf=clock();
    cout << "tempo:" << (double)(tf-ti)/CLOCKS_PER_SEC << endl;

    for(int i=0; i<10; ++i)
        result << tempoCC[i] << ";" << tempoSC[i] << endl;
    result.close();
}
