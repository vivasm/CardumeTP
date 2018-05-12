#ifndef WORKER_H
#define WORKER_H
#include <QThread>
#include "ambiente.h"


class worker : public QThread
{
public:
    worker(ambiente *obj);
    void run();
    ambiente *subOceano;
    int popS;
    int tempo;
};

#endif // WORKER_H
