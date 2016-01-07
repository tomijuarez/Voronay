#ifndef TRIANGULO_H
#define TRIANGULO_H

#include <QPair>
#include <QDebug>
#include <QList>
#include "circunscripta.h"

class Triangulo
{
public:
    Triangulo();
    Triangulo(QPair<double, double> punto1, QPair<double, double> punto2, QPair<double, double> punto3);
    void definirPuntos(QPair<double, double> punto1, QPair<double, double> punto2, QPair<double, double> punto3);
    bool tieneDentro(QPair<double, double> punto);
    bool estaEnUnLado(QPair<double, double> punto);
    bool contieneArista(QPair<double, double> punto1,QPair<double, double> punto2);
    QList<QPair<QPair<double, double>, QPair<double, double> > > getAristas();
    QList<QPair<double, double> > getVertices();
    Circunscripta * getCircunscripta();
    bool contienePunto(QPair<double, double> punto);
    void imprimir();
    ~Triangulo();
private:
    double area(QPair<double, double> punto1, QPair<double, double> punto2, QPair<double, double> punto3);
    QPair<double, double> punto1;
    QPair<double, double> punto2;
    QPair<double, double> punto3;
};

#endif // TRIANGULO_H
