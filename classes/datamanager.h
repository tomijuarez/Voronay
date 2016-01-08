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
        void drawLine(double x1, double y1, double x2, double y2);
        void drawPoint(double x, double y);
        void drawCircle(double x, double y, double radius);
        void cleanScene();
    public slots:
        void addPoint(double x, double y);
        void clear();
        void reset();
        void initIncrementalAlgorithm();

    private:
        void triangulate();
        void tessellate();
        void drawTriangles();
        void drawPoints();
        void drawLines();
        void drawCircuncentros();

        Delaunay delaunay;
        Voronoi voronoi;
        Triangulo * externTriangle;
        QList<QPair<double, double> > points;
        QList<QPair<double, double> > circuncentros;
        QList<Triangulo *> triangulation;
        QList<QPair<QPair<double, double>, QPair<double, double> > > aristas;

        bool cambio = false;
        bool calculada = false;
};

#endif // DATAMANAGER_H
