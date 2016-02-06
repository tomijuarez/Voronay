#ifndef VORONOI_H
#define VORONOI_H

#include <QList>
#include <QPair>
#include "triangulo.h"
#include "grafohistorico.h"
#include "triangulo.h"
#include "arista.h"
#include "circunscripta.h"
#include "voronoicells.h"

class Voronoi
{
public:
    QList<QPair<double, double> > getCentroides();
    Voronoi();
    ~Voronoi();
    void calcular(GrafoHistorico *grafoDelaunay, NodoGrafo *listaTriangulos, QPair<double, double> p1, QPair<double, double> p2, QPair<double, double> p3);
    QList<QPair<QPair<double, double>, QPair<double, double> > > getAristas();
    QList<QPair<double,double> > getCircuncentros();
    QList<Circunscripta *> getCircunscriptas();
    void clear();

private:
    QPair<double, double> midPoint(QPair<QPair<double, double>, QPair<double,double> > arista);
    double pendiente(QPair<double, double> p1, QPair<double,double> p2);
    void agregarArista(QPair<double,double>, QPair<double, double>);


    QList<QPair<QPair<double, double>, QPair<double, double> > > aristas;
    QList<QPair<double, double> > circuncentros;
    QList<Circunscripta *> circunscriptas;

    QList<Arista> aristasVoronoi;
    QList<QPair<double, double> > centros;

    QList<QPair<double,double> > centroides;

    VoronoiCells celdas;
};

#endif // VORONOI_H
