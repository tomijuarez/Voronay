#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <QQuickItem>
#include <QList>
#include <QPair>
#include "delaunay.h"
#include "triangulo.h"
#include "voronoi.h"

class DataManager : public QObject {
    Q_OBJECT

    signals:
        void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3);
        void drawLine(float x, float y);
        void drawPoint(float x, float y);
        void cleanScene();
    public slots:
        void addPoint(float x, float y);
        void reset();
        void initIncrementalAlgorithm();
        void initFortunesAlgorithm();

    private:
        void triangulate();
        void drawTriangles(QList<Triangulo *> triangles);

        Delaunay delaunay;
        Voronoi voronoi;
        Triangulo * externTriangle;
        QList<QPair<float, float> > points;
        bool calculada;
        bool cambio;


};

#endif // DATAMANAGER_H
