#include <QCoreApplication>
#include "ambiente.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <time.h>
#include "worker.h"

using namespace std;
inline bool exists_test (const std::string& name) {
    ifstream f(name.c_str());
    return f.good();
}


int main(int argc, char *argv[])
{
    ofstream result;
    clock_t ti,tf;
    int popS=atoi(argv[1]);
    int popT=atoi(argv[2]); // população de tubarões
    int nAmo=atoi(argv[3]);
    bool fex=exists_test("resultadoTese.csv");
    result.open("resultadoTese.csv",fstream::app);
    if(!fex)
        result << "popS;popT;Gamma;Tccm;TCCsd;Tscm;TSCsd" <<endl;
    ti=clock();

    double tempoCC[nAmo], tempoSC[nAmo];

    #pragma omp parallel for num_threads(4)
    for(int si=1;si<=nAmo;si++)
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
    double gamma=0;
    int somaCC=0,somaCC2=0;
    int somaSC=0,somaSC2=0;
    for(int i=0; i<nAmo; ++i)
    {
        gamma+=(tempoCC[i]>tempoSC[i]);
        somaCC+=tempoCC[i];
        somaCC2+=(tempoCC[i]*tempoCC[i]);
        somaSC+=tempoSC[i];
        somaSC2+=(tempoSC[i]*tempoSC[i]);
    }
    double CCm=somaCC/nAmo;
    double CCdesv=sqrt((double)somaCC2/nAmo-CCm*CCm);
    double SCm=somaSC/nAmo;
    double SCdesv=sqrt((double)somaSC2/nAmo-SCm*SCm);
    result << (string)argv[1]+";"+(string)argv[2]+";" << (double)gamma/nAmo
           << ";" <<CCm << ";" << CCdesv
           << ";" <<SCm << ";" << SCdesv << endl;
    result.close();
}
