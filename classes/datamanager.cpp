#include "datamanager.h"
#include <QDebug>

void DataManager::initIncrementalAlgorithm() {
    QPair<double, double> punto1(0,9000);
    QPair<double, double> punto2(1000,-1000);
    QPair<double, double> punto3(-1000,-1000);
    Triangulo triangulo(punto1,punto2,punto3);
    this->externTriangle = &(triangulo);
    this->calculada = true;
    this->triangulate();
}

void DataManager::initFortunesAlgorithm() {
    this->tesel();
}

void DataManager::tesel(){
    GrafoHistorico * grafoDelaunay = this->delaunay.getGrafoHistorico();
    QList<QPair<double,double> > aristasVoronoi = this->voronoi.calcular(grafoDelaunay);
    QPair<double,double> arista;
    foreach(arista,aristasVoronoi){
        this->drawLine(arista.first,arista.second);
    }
}

void DataManager::clear() {
    this->triangulation.clear();
    this->points.clear();
    this->cambio = true;
}

void DataManager::addPoint(double x, double y) {
        QPair<double, double> punto(x,y);
        this->points.push_back(punto);
        this->cambio = true;
    if(this->calculada){
        this->delaunay.agregarPunto(punto);
        this->triangulation = this->delaunay.triangular();
        this->drawTriangles();
        this->drawPoints();
        this->cambio = false;
     }
}

/**
 * Privados
 */

void DataManager::reset(){
    this->points.clear();
    this->triangulation.clear();
    this->delaunay.resetear();
    this->cleanScene();
    this->calculada = false;
}

void DataManager::triangulate() {
    if (this->cambio) {
        this->delaunay.setTrianguloExterior(this->externTriangle);
        this->delaunay.setPuntos(this->points);
        this->triangulation = this->delaunay.triangular();
    }

    qDebug() << " *------------------------* Hay " << this->points.size();

    this->drawTriangles();
    this->drawPoints();

    this->cambio = false;
}

void DataManager::drawPoints() {
    QPair<double, double> point;
    foreach(point, this->points) {
        this->drawPoint(point.first, point.second);
    }
}

void DataManager::drawTriangles() {
    this->cleanScene();
    foreach(Triangulo * triangle, this->triangulation) {
        QList<QPair<double, double>> vertices = triangle->getVertices();
        QPair<double,double> vertice1 = vertices.at(0);
        QPair<double,double> vertice2 = vertices.at(1);
        QPair<double,double> vertice3 = vertices.at(2);
        this->drawTriangle(vertice1.first, vertice1.second, vertice2.first, vertice2.second, vertice3.first, vertice3.second);
    }
}

