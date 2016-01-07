#ifndef VORONOI_H
#define VORONOI_H

#include <QList>
#include <QPair>
#include "triangulo.h"
#include "grafohistorico.h"

class Voronoi
{
public:
    Voronoi();
    ~Voronoi();
    QList<QPair<float,float> > calcular(GrafoHistorico * grafoDelaunay);
};

#endif // VORONOI_H
