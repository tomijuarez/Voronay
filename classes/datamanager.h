#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <QQuickItem>
#include <QList>
#include <QPair>
#include "delaunay.h"
#include "triangulo.h"
#include "voronoi.h"
#include "circunscripta.h"

class DataManager : public QObject {
    Q_OBJECT

    signals:
        void drawTriangle(double x1, double y1, double x2, double y2, double x3, double y3);
        void drawLine(double x1, double y1, double x2, double y2);
        void drawPoint(double x, double y);
        void drawCircle(double x, double y, double radius);
        void drawPaintedCircle(double x, double y, double radius);
        void drawAxis();
        void cleanScene();
    public slots:
        void addPoint(double x, double y);
        void clear();
        void reset();
        void initIncrementalAlgorithm();
        void refresh();
        void changeDrawTriangles();
        void changeDrawCircles();
        void changeDrawVoronoi();

    private:
        void drawCenterOfMass();
        void triangulate();
        void tessellate();
        void draw();
        void drawTriangles();
        void drawPoints();
        void drawLines();
        void drawCircuncentros();
        void drawCircunscriptas();

        Delaunay delaunay;
        Voronoi voronoi;
        Triangulo * externTriangle;
        QList<QPair<double, double> > points;
        QList<QPair<double, double> > circuncentros;
        QList<Circunscripta*> circunscriptas;
        QList<Triangulo *> triangulation;
        QList<QPair<QPair<double, double>, QPair<double, double> > > aristas;

        bool cambio = false;
        bool calculada = false;
        bool triangulosActivos = true;
        bool circulosActivos = true;
        bool voronoiActivo = true;
};

#endif // DATAMANAGER_H
