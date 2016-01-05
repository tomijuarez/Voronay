#ifndef CIRCUNSCRIPTA_H
#define CIRCUNSCRIPTA_H

#include <QPair>
#include <math.h>

class Circunscripta
{
public:
    /**
     * Genera la circunferencia circunscripta del triángulo.
     */
    Circunscripta(QPair<float, float> punto1, QPair<float, float> punto2, QPair<float, float> punto3);
    ~Circunscripta();
    QPair<float, float> getCentro() const;
    float getRadio() const;
    bool estaDentro(QPair<float, float> punto) const;

private:
    float pendienteMediatriz(QPair<float,float> punto1, QPair<float,float> punto2);
    QPair<float,float> medio(QPair<float,float> punto1, QPair<float,float> punto2);
    QPair<float,float> interseccion(float m1, float m2, float b1, float b2);
    float radio;
    QPair<float, float> centro;
};

#endif // CIRCUNSCRIPTA_H
