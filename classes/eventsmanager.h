#ifndef EVENTSMANAGER_H
#define EVENTSMANAGER_H

#include <QObject>
#include <QQuickItem>
#include <QList>
#include <QPair>
#include "delaunay.h"
#include "triangulo.h"
#include "voronoi.h"

class EventsManager : public QObject {
    Q_OBJECT

    signals:
        void dibujarTriangulo(QPair<float, float> punto1, QPair<float, float> punto2, QPair<float, float> punto3);
    public slots:
        void agregarVertice(QPair<float, float> punto);
        void reset();
        void initIncrementalAlgorithm();
        void initFortunesAlgorithm();

    private:
        void dibujarTriangulos(QList<Triangulo *> triangulos);
        void triangular();
        void teselar();

        QList<QPair<float, float> > nubeDePuntos;
        Delaunay delaunay;
        Voronoi voronoi;

        Triangulo * trianguloExterior;

        QList<Triangulo *> triangulacion;
        bool cambio;
};


#endif // EVENTSMANAGER_H
