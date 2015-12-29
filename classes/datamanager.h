#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <QQuickItem>
#include <QList>
#include <QPair>

class DataManager : public QObject {
    Q_OBJECT

    signals:
        void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3);
        void drawLine(float x, float y);
    public slots:
        void addPoint(float x, float y) {
            QPair<float, float> point(x,y);
            this->points.push_back(point);
        }

        void initIncrementalAlgorithm();

        void initFortunesAlgorithm();

        void initDelaunay() {

        }

        void initVoronoi() {

        }

    private:
        QList<QPair<float, float>> points;

        //void drawTriangles(QList<Triangulo> triangulos);
        //void drawTesellation(QList<Line> lines);
};

#endif // DATAMANAGER_H
