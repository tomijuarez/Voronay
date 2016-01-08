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
        void drawTriangle(double x1, double y1, double x2, double y2, double x3, double y3);
        void drawLine(double x, double y);
        void drawPoint(double x, double y);
        void cleanScene();
    public slots:
        void addPoint(double x, double y);
        void clear();
        void reset();
        void initIncrementalAlgorithm();
        void initFortunesAlgorithm();

    private:
        void triangulate();
        void tesel();
        void drawTriangles();
        void drawPoints();

        Delaunay delaunay;
        Voronoi voronoi;
        Triangulo * externTriangle;
        QList<QPair<double, double> > points;
        QList<Triangulo *> triangulation;

        bool cambio = false;
        bool calculada = false;
};

#endif // DATAMANAGER_H
