#ifndef VORONOICELLS_H
#define VORONOICELLS_H

#include <QPair>
#include <QList>
#include <QSet>
#include <QDebug>
#include <qmath.h>

#include "arista.h"

class VoronoiCells
{
public:
    VoronoiCells();
    QList<QPair<double,double> > centroides(QList<QPair<double,double> > points, QList<Arista> edges);


private:
    double area_for_polygon(QList<QPair<double,double> > polygon);
    QPair<double,double> centroid_for_polygon(QList<QPair<double,double> > polygon);
    int bottommost_index_for_polygon(QList<QPair<double,double> > polygon);
    double angle_for_vector(QPair<double,double> start_point, QPair<double,double> end_point);
    QList<QPair<double,double> > convex_hull_for_polygon(QList<QPair<double,double> > polygon);
    QPair<double,double> midPoint(Arista arista);
    bool counterClockWise(QPair<double,double> A, QPair<double,double> B, QPair<double,double> C);
    bool intersects(Arista arista1, Arista arista2);
    QList<QPair<double,double>> polygonPoints(QList<Arista> edges);
};

#endif // VORONOICELLS_H
