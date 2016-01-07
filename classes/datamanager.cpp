#include "datamanager.h"
#include "delaunay.h"
#include "grafohistorico.h"
#include "voronoi.h"
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
    this->tesel();
}

void DataManager::addPoint(float x, float y) {
    QPair<float, float> punto(x,y);
    this->points.push_back(punto);
    this->cambio = true;
}

void DataManager::reset(){
    this->delaunay.resetear();
}

/**
 * Privados
 */

void DataManager::triangulate() {

        this->delaunay.setTrianguloExterior(this->externTriangle);
        this->delaunay.setPuntos(this->points);
        this->points.clear();
        this->drawTriangles(this->delaunay.triangular());

    this->cambio = false;
}

void DataManager::tesel(){
    GrafoHistorico * grafoDelaunay = this->delaunay.getGrafoHistorico();
    QList<QPair<float,float> > aristasVoronoi = this->voronoi.calcular(grafoDelaunay);
    QPair<float,float> arista;
    foreach(arista,aristasVoronoi){
        this->drawLine(arista.first,arista.second);
    }
}

void DataManager::drawTriangles(QList<Triangulo *> triangulos) {
    this->cleanScene();
    foreach(Triangulo * triangulo, triangulos) {
        QList<QPair<float, float>> vertices = triangulo->getVertices();
        QPair<float,float> vertice1 = vertices.at(0);
        QPair<float,float> vertice2 = vertices.at(1);
        QPair<float,float> vertice3 = vertices.at(2);
        this->drawTriangle(vertice1.first, vertice1.second, vertice2.first, vertice2.second, vertice3.first, vertice3.second);
        qDebug() << "Sale triangulo.";
    }
}

