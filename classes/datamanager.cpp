#include "datamanager.h"
#include <QDebug>

void DataManager::initIncrementalAlgorithm() {
    QPair<double, double> punto1(0,9000);
    QPair<double, double> punto2(1000,-1000);
    QPair<double, double> punto3(-1000,-1000);
    Triangulo triangulo(punto1,punto2,punto3);
    this->externTriangle = &(triangulo);
    this->calculada = true;
    this->cleanScene();
    this->triangulate();
    this->tessellate();
    this->cambio = false;
}

void DataManager::refresh(){
    this->drawCircuncentros();
    this->drawCircunscriptas();
    this->drawLines();
    this->drawTriangles();
}

void DataManager::drawLines() {
    QPair<QPair<double, double>, QPair<double, double> > arista;
    foreach(arista, this->aristas) {
        this->drawLine(arista.first.first, arista.first.second, arista.second.first, arista.second.second);
    }
}

void DataManager::clear() {
    this->triangulation.clear();
    this->aristas.clear();
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
        GrafoHistorico * grafoDelaunay = this->delaunay.getGrafoHistorico();
        this->voronoi.calcular(grafoDelaunay);
        this->aristas = this->voronoi.getAristas();
        this->circuncentros = this->voronoi.getCircuncentros();
        this->circunscriptas = this->voronoi.getCircunscriptas();
        this->cleanScene();
        this->drawTriangles();
        this->drawLines();
        this->drawPoints();
        this->drawCircuncentros();
        this->drawCircunscriptas();
        this->cambio = false;
     }
}

/**
 * Privados
 */

void DataManager::reset(){
    this->points.clear();
    this->circuncentros.clear();
    this->triangulation.clear();
    this->delaunay.resetear();
    this->aristas.clear();
    this->voronoi.clear();
    this->cleanScene();
    this->calculada = false;
}

void DataManager::triangulate() {
    if (this->cambio) {
        this->delaunay.setTrianguloExterior(this->externTriangle);
        this->delaunay.setPuntos(this->points);
        this->triangulation = this->delaunay.triangular();
    }

    this->drawTriangles();
    this->drawPoints();
}

void DataManager::tessellate(){
    if(this->cambio){
        GrafoHistorico * grafoDelaunay = this->delaunay.getGrafoHistorico();
        this->voronoi.calcular(grafoDelaunay);
        this->aristas = voronoi.getAristas();
        this->circuncentros = this->voronoi.getCircuncentros();
        this->circunscriptas = this->voronoi.getCircunscriptas();
    }
    this->drawLines();
    this->drawCircuncentros();
    this->drawCircunscriptas();
}

void DataManager::drawPoints() {
    QPair<double, double> point;
    foreach(point, this->points) {
        this->drawPoint(point.first, point.second);
    }
}

void DataManager::drawCircuncentros() {
    QPair<double, double> point;
    foreach(point, this->circuncentros) {
        this->drawPaintedCircle(point.first, point.second,3);
    }
}

void DataManager::drawCircunscriptas() {
    Circunscripta * circ;
    foreach(circ, this->circunscriptas) {
        QPair<double,double> centro = circ->getCentro();
        this->drawCircle(centro.first,centro.second,circ->getRadio());
    }
}

void DataManager::drawTriangles() {
    foreach(Triangulo * triangle, this->triangulation) {
        QList<QPair<double, double>> vertices = triangle->getVertices();
        QPair<double,double> vertice1 = vertices.at(0);
        QPair<double,double> vertice2 = vertices.at(1);
        QPair<double,double> vertice3 = vertices.at(2);
        this->drawTriangle(vertice1.first, vertice1.second, vertice2.first, vertice2.second, vertice3.first, vertice3.second);
    }
}

