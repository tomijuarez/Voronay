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
    Circunscripta(QPair<double, double> punto1, QPair<double, double> punto2, QPair<double, double> punto3);
    ~Circunscripta();
    QPair<double, double> getCentro() const;
    double getRadio() const;
    bool estaDentro(QPair<double, double> punto) const;

private:
    double pendienteMediatriz(QPair<double,double> punto1, QPair<double,double> punto2);
    QPair<double,double> medio(QPair<double,double> punto1, QPair<double,double> punto2);
    QPair<double,double> interseccion(double m1, double m2, double b1, double b2);
    double radio;
    QPair<double, double> centro;
};

#endif // CIRCUNSCRIPTA_H
