#ifndef AMBIENTE_H
#define AMBIENTE_H
#include "agente.h"
#include <vector>
using namespace std;

class ambiente
{
public:
    ambiente(int N, int Nt);
    ambiente();
    void roda();
    double getTamM() const;
    int getNAg() { return this->ag.size();}
    posicao getPosAg(int i);
    double getRaiViz(int i);
    double getDir(int i);
    bool getEhSardinha(int i);

private:
    vector <agente> ag;
    vector <int> in;
    double tamM;
    void atuPerc();
    void rodaModelo();
    void atuacao();
    double calcDist(int i, int j);
};

#endif // AMBIENTE_H
