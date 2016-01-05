#ifndef VORONOI_H
#define VORONOI_H

#include <QList>
#include <QPair>
#include "triangulo.h"

class Voronoi
{
public:
    Voronoi();
    ~Voronoi();
    QList<QPair<float,float> > calcular(QList<Triangulo>);
};

#endif // VORONOI_H
