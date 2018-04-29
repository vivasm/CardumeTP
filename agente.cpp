#include "agente.h"
#include <stdlib.h>
#include <math.h>
#define PI 3.1416

agente::agente()
{
    static int cnt=0;
    this->loc.x=(double)rand()/RAND_MAX;
    this->loc.y=(double)rand()/RAND_MAX;
    this->passo=0.01;
    this->dir=(double)rand()/RAND_MAX*360;
    this->raiViz=5*this->passo;
    this->raiMorte=this->passo;
    this->toMorto=false;
    this->angV=40;
    this->vx=this->vy=0;
    this->id=cnt++;
    double dado=(double)rand()/RAND_MAX;
    if(dado>0.98)
    {
        this->ehSardinha=false;
        this->passo=0.02;
    }
    else this->ehSardinha=true;
}

agente::agente(bool ehSardinha)
{
    static int cnt=0;
    this->loc.x=(double)rand()/RAND_MAX;
    this->loc.y=(double)rand()/RAND_MAX;
    this->passo=0.01;
    this->dir=(double)rand()/RAND_MAX*360;
    this->raiViz=5*this->passo;
    this->raiMorte=this->passo;
    this->toMorto=false;
    this->angV=40;
    this->vx=this->vy=0;
    this->id=cnt++;
    if(!ehSardinha)
    {
        this->ehSardinha=false;
        this->passo=0.02;
    }
    else this->ehSardinha=true;
}


double condCont(double p)
{
    if(p>1) return p-=1;
    if(p<0) return p+=1;
    return p;
}

void agente::rodaModelo()
{
    // condições de contorno
    this->loc.x=condCont(this->loc.x);
    this->loc.y=condCont(this->loc.y);

    if(this->ehSardinha) // Sou Sardinha?
    {
        bool temTubarao=false;
        agente *tubarao;
        for(int i=0;i<this->viz.size();i++)
        {
            if(!this->viz[i]->ehSardinha)
            {
                temTubarao=true;
                tubarao=this->viz[i];
                break;
            }
        }
        this->passo=0.01;
        if(temTubarao)
        {
            if(morri(tubarao)) // se distancia é menor do que a critica
            {
                this->toMorto=true;
            }
            else
            {
                this->passo=0.015;
                this->saiCorrendo(tubarao);
            }
        }
        else if(this->viz.size()>0)
        {
            this->vaiComAGalera();
            this->vaiDeBoa();
        }
        else
            this->vaiDeBoa();
    }
    else        // Sou Tubarão!
    {
        this->vaiDeBoa();
    }
}







void agente::atua()
{
    this->loc.x+=this->vx;
    this->loc.y+=this->vy;
}

posicao agente::getLoc() const
{
    return loc;
}

double agente::getRaiViz() const
{
    return raiViz;
}

void agente::addViz(agente *pag)
{
    this->viz.push_back(pag);
}

void agente::cleanViz()
{
    this->viz.clear();
}

double agente::getDir() const
{
    return dir;
}

bool agente::getEhSardinha() const
{
    return ehSardinha;
}

double agente::getRaiMorte() const
{
    return raiMorte;
}

bool agente::getToMorto() const
{
    return toMorto;
}

void agente::saiCorrendo(agente *tb)
{
    posicao pT=tb->getLoc();
    posicao pM=this->getLoc();
    this->dir=atan2(pT.y-pM.y,pT.x-pM.x)*180/PI+180;
    this->vx=this->passo*cos(this->dir*PI/180);
    this->vy=this->passo*sin(this->dir*PI/180);

}

void agente::vaiComAGalera()
{
    // percepcao vizinhos
    double mdir=0;
    for(int i=0;i<this->viz.size();i++)
    {
        mdir+=this->viz[i]->dir;
    }
    mdir/=this->viz.size();
    this->dir=mdir;
}

void agente::vaiDeBoa()
{
    double na=(double)rand()/RAND_MAX;
    this->dir+=(na-0.5)*this->angV;
    this->vx=this->passo*cos(this->dir*PI/180);
    this->vy=this->passo*sin(this->dir*PI/180);
}

bool agente::morri(agente *tb)
{
    posicao pT=tb->getLoc();
    posicao pM=this->getLoc();
    double d,dx,dy;
    dx=pT.x-pM.x;
    dy=pT.y-pM.y;
    d=sqrt(dx*dx+dy*dy);
    if(d<=this->raiMorte)
        return true;
    else
        return false;
}


