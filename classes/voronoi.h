#ifndef VORONOI_H
#define VORONOI_H

#include <QList>
#include <QPair>
#include "triangulo.h"
#include "grafohistorico.h"
#include <QList>
#include <QMap>
#include "triangulo.h"
#include "arista.h"
#include "circunscripta.h"

class Voronoi
{
public:
    Voronoi();
    ~Voronoi();
    void calcular(GrafoHistorico * grafoDelaunay);
    QList<QPair<QPair<double, double>, QPair<double, double> > > getAristas();
    QList<QPair<double,double> > getCircuncentros();
    QList<Circunscripta *> getCircunscriptas();
    void clear();

private:
    QPair<double, double> midPoint(QPair<QPair<double, double>, QPair<double,double> > arista);
    void agregarArista(QPair<double,double>, QPair<double, double>);


    QList<QPair<QPair<double, double>, QPair<double, double> > > aristas;
    QList<QPair<double, double> > circuncentros;
    QList<Circunscripta *> circunscriptas;
};

#endif // VORONOI_H
