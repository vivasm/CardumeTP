#ifndef AGENTE_H
#define AGENTE_H
#include "pos.h"
#include <vector>
using namespace std;


class agente
{
public:
    agente(bool ehSardinha);
    agente();
    void rodaModelo();
    void atua();
    posicao getLoc() const;
    double getRaiViz() const;
    void addViz(agente *pag);
    void cleanViz();

    double getDir() const;

    bool getEhSardinha() const;

    double getRaiMorte() const;

    bool getToMorto() const;

private:
    int id;
    bool ehSardinha;
    posicao loc;
    double dir;                 // direção do movimento
    double angV;                // Angulo de visão
    double passo;
    vector <agente *> viz;
    double raiViz;
    double raiMorte;
    bool toMorto;
    double vx,vy;
    void saiCorrendo(agente *tb);
    void vaiComAGalera();
    void vaiDeBoa();
    bool morri(agente *tb);

};

#endif // AGENTE_H
