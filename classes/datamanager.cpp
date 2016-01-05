#include "datamanager.h"
#include <QDebug>

void DataManager::initIncrementalAlgorithm() {
    QPair<float, float> punto1(0,10000);
    QPair<float, float> punto2(10000,-10000);
    QPair<float, float> punto3(-10000,-10000);
    Triangulo triangulo(punto1,punto2,punto3);
    this->externTriangle = &(triangulo);
    this->triangulate();
}

void DataManager::initFortunesAlgorithm() {
    QPair<float, float> punto1(-1000,1000);
    QPair<float, float> punto2(1000,1000);
    QPair<float, float> punto3(0,-1000);
    Triangulo triangulo(punto1,punto2,punto3);
    this->externTriangle = &(triangulo);
    this->triangulate();
}

void DataManager::addPoint(float x, float y) {
    QPair<float, float> punto(x,y);
    this->points.push_back(punto);
    this->cambio = true;
}

/**
 * Privados
 */

void DataManager::reset() {
    this->points.clear();
}

void DataManager::triangulate() {
    if ( this->cambio ) {
        this->delaunay.setTrianguloExterior(this->externTriangle);
        this->delaunay.setPuntos(this->points);
        this->drawTriangles(this->delaunay.triangular());
    }
    this->cambio = false;
}

void DataManager::drawTriangles(QList<Triangulo *> triangulos) {
    foreach(Triangulo * triangulo, triangulos) {
        QList<QPair<float, float>> vertices = triangulo->getVertices();
        QPair<float,float> vertice1 = vertices.at(0);
        QPair<float,float> vertice2 = vertices.at(1);
        QPair<float,float> vertice3 = vertices.at(2);
        this->drawTriangle(vertice1.first, vertice1.second, vertice2.first, vertice2.second, vertice3.first, vertice3.second);
        qDebug() << "Sale triangulo.";
    }
}

