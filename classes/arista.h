#ifndef ARISTA_H
#define ARISTA_H

#include <QPair>
#include <QDebug>

class Arista
{
public:
    Arista();
    void setPuntos(QPair<double,double> inicio, QPair<double,double> fin);
    QPair<double,double> getInicio();
    QPair<double,double> getFin();
private:
    QPair<double,double> inicio;
    QPair<double,double> fin;
};

#endif // ARISTA_H
