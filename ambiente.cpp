#include "ambiente.h"
#include <math.h>
#include <algorithm>

ambiente::ambiente()
{
    this->tamM=1000;
    for(int i=0;i<201;i++)
    {
        this->in.push_back(i);
        agente finn;
        this->ag.push_back(finn);
    }
}
ambiente::ambiente(int Ns,int Nt,bool temCardume)
{
    this->tamM=1000;
    this->nSard=Ns;
    for(int i=0;i<Ns;i++)
    {
        this->in.push_back(i);
        agente finn(true,temCardume);
        this->ag.push_back(finn);
    }
    for(int i=0;i<Nt;i++)
    {
        this->in.push_back(i+Ns);
        agente finn(false,temCardume);
        this->ag.push_back(finn);
    }
}

void ambiente::roda()
{
    this->atuPerc();
    this->rodaModelo();
    this->atuacao();
}

double ambiente::getTamM() const
{
    return tamM;
}

posicao ambiente::getPosAg(int i)
{
    posicao pa=this->ag[i].getLoc();
    pa.x*=this->tamM;
    pa.y*=this->tamM;
    return pa;
}

double ambiente::getRaiViz(int i)
{
    return this->ag[i].getRaiViz()*this->tamM;
}

double ambiente::getDir(int i)
{
    return this->ag[i].getDir();
}

bool ambiente::getEhSardinha(int i)
{
    return this->ag[i].getEhSardinha();
}

int ambiente::getNSard() const
{
    return nSard;
}

void ambiente::atuPerc()
{
    double d;
    for(int i=0;i<this->ag.size();i++)
    {
        this->ag[i].cleanViz();
        for(int j=0;j<this->ag.size();j++)
        {
            if(i!=j)
            {
                d=this->calcDist(i,j);
                if(d<=this->ag[i].getRaiViz())
                {
                    this->ag[i].addViz(&this->ag[j]);
                }

            }
        }
    }
}

void ambiente::rodaModelo()
{
    for(int i=0;i<this->ag.size();i++)
    {
        this->ag[in[i]].rodaModelo();
    }
    shuffle(in.begin(),in.end(),std::default_random_engine(1));
}

void ambiente::atuacao()
{
    for(int i=0;i<this->ag.size();i++)
    {
        if(this->ag[i].getToMorto())
        {
            this->ag.erase(this->ag.begin()+i);
            this->nSard--;
        }
        else
            this->ag[i].atua();
    }

}

double ambiente::calcDist(int i, int j)
{
    double dist=0;
    posicao posI,posJ;
    posI=this->ag[i].getLoc();
    posJ=this->ag[j].getLoc();
    double dx,dy;
    dx=posI.x-posJ.x;
    dy=posI.y-posJ.y;
    dist= sqrt(dx*dx+dy*dy);
    return dist;
}
