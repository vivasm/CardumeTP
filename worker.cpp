#include "worker.h"

worker::worker(ambiente *obj)
{
    this->subOceano=obj;
    this->popS=obj->getNSard();
}

void worker::run()
{
    this->tempo=0;
    while(this->subOceano->getNSard()>this->popS/2)
    {
        this->subOceano->roda();
        this->tempo++;
    }
}
