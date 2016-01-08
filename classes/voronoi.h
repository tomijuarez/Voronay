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

class Voronoi
{
public:
    Voronoi();
    ~Voronoi();
    void calcular(GrafoHistorico * grafoDelaunay);
    QList<QPair<QPair<double, double>, QPair<double, double> > > getAristas();
    void clear();

private:
    QPair<double, double> midPoint(QPair<QPair<double, double>, QPair<double,double> > arista);
    void agregarArista(QPair<double,double>, QPair<double, double>);


    QList<QPair<QPair<double, double>, QPair<double, double> > > aristas;
};

#endif // VORONOI_H
