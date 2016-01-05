#include "eventsmanager.h"

void EventsManager::initIncrementalAlgorithm() {
    QPair<float, float> punto1(-1000,1000);
    QPair<float, float> punto2(1000,1000);
    QPair<float, float> punto3(0,-1000);
    Triangulo triangulo(punto1,punto2,punto3);
    this->trianguloExterior = &(triangulo);
}

void EventsManager::agregarVertice(QPair<float, float> punto) {
    nubeDePuntos.push_back(punto);
    this->cambio = true;
}

void EventsManager::reset() {
    this->nubeDePuntos.clear();
}

/**
 * Privados
 */

void EventsManager::triangular() {
    if ( this->cambio ) {
        this->delaunay.setTrianguloExterior(this->trianguloExterior);
        this->delaunay.setPuntos(this->nubeDePuntos);
        this->triangulacion = this->delaunay.triangular();
    }
    this->cambio = false;
}

void EventsManager::dibujarTriangulos(QList<Triangulo *> triangulos) {
    foreach(Triangulo * triangulo, triangulos) {
        QList<QPair<float, float>> vertices = triangulo->getVertices();
        this->dibujarTriangulo(vertices.at(0), vertices.at(1), vertices.at(2));
        qDebug() << "Sale triangulo.";
    }
}

void EventsManager::teselar() {

}
