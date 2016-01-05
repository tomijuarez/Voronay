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
    Triangulo(QPair<float, float> punto1, QPair<float, float> punto2, QPair<float, float> punto3);
    void definirPuntos(QPair<float, float> punto1, QPair<float, float> punto2, QPair<float, float> punto3);
    bool tieneDentro(QPair<float, float> punto);
    bool estaEnUnLado(QPair<float, float> punto);
    bool contieneArista(QPair<float, float> punto1,QPair<float, float> punto2);
    QList<QPair<QPair<float, float>, QPair<float, float> > > getAristas();
    QList<QPair<float, float> > getVertices();
    Circunscripta * getCircunscripta();
    bool contienePunto(QPair<float, float> punto);
    void imprimir();
    ~Triangulo();
private:
    float area(QPair<float, float> punto1, QPair<float, float> punto2, QPair<float, float> punto3);
    QPair<float, float> punto1;
    QPair<float, float> punto2;
    QPair<float, float> punto3;
};

#endif // TRIANGULO_H
