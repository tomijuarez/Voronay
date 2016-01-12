#include "datamanager.h"
#include <QDebug>

void DataManager::initIncrementalAlgorithm() {
    if(this->points.count() > 2){
        QPair<double, double> punto1(0,70000);
        QPair<double, double> punto2(70000,-70000);
        QPair<double, double> punto3(-70000,-70000);
        Triangulo triangulo(punto1,punto2,punto3);
        this->externTriangle = &(triangulo);
        this->calculada = true;
        this->triangulate();
        this->tessellate();
        this->draw();
        this->cambio = false;
    }
}

void DataManager::refresh(){
    this->draw();
}

void DataManager::changeDrawTriangles(){
    this->triangulosActivos = !this->triangulosActivos;
}

void DataManager::changeDrawCircles(){
    this->circulosActivos = !this->circulosActivos;
}

void DataManager::changeDrawVoronoi(){
    this->voronoiActivo = !this->voronoiActivo;
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
        this->voronoi.calcular(this->delaunay.getGrafoHistorico(),this->delaunay.getListaTriangulos(),this->delaunay.getP1(),this->delaunay.getP2(),this->delaunay.getP3());
        this->aristas = this->voronoi.getAristas();
        this->circuncentros = this->voronoi.getCircuncentros();
        this->circunscriptas = this->voronoi.getCircunscriptas();
        this->draw();
        this->cambio = false;
     }
}

/**
 * Privados
 */

void DataManager::reset(){
    this->points.clear();
    this->circuncentros.clear();
    this->circunscriptas.clear();
    this->triangulation.clear();
    this->delaunay.resetear();
    this->aristas.clear();
    this->voronoi.clear();
    this->cleanScene();
    this->draw();
    this->calculada = false;
}

void DataManager::triangulate() {
    if (this->cambio) {
        this->delaunay.setTrianguloExterior(this->externTriangle);
        this->delaunay.setPuntos(this->points);
        this->delaunay.triangular();
    }
}

void DataManager::tessellate(){
    if(this->cambio){
        this->voronoi.calcular(this->delaunay.getGrafoHistorico(),this->delaunay.getListaTriangulos(),this->delaunay.getP1(),this->delaunay.getP2(),this->delaunay.getP3());
        this->aristas = this->voronoi.getAristas();
        this->aristas = voronoi.getAristas();
        this->circuncentros = this->voronoi.getCircuncentros();
        this->circunscriptas = this->voronoi.getCircunscriptas();
    }
}

void DataManager::draw(){
    this->cleanScene();
    this->drawAxis();
    if(this->triangulosActivos){
        this->drawTriangles();
        this->drawPoints();
    }
    if(this->circulosActivos || this->voronoiActivo){
        this->drawCircuncentros();
        if(this->circulosActivos){
            this->drawCircunscriptas();
        }
        if(this->voronoiActivo){
            this->drawLines();
        }
    }
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
        NodoGrafo * actual = this->delaunay.getListaTriangulos();
        while(actual != NULL){
            if(actual->getTriangulo()->contienePunto(this->delaunay.getP1()) ||
               actual->getTriangulo()->contienePunto(this->delaunay.getP2()) ||
               actual->getTriangulo()->contienePunto(this->delaunay.getP3())){

            }else{
                QList<QPair<double, double>> vertices = actual->getTriangulo()->getVertices();
                QPair<double,double> vertice1 = vertices.at(0);
                QPair<double,double> vertice2 = vertices.at(1);
                QPair<double,double> vertice3 = vertices.at(2);
                this->drawTriangle(vertice1.first, vertice1.second, vertice2.first, vertice2.second, vertice3.first, vertice3.second);
            }
            actual = actual->getSigHoja();
        }
}

