#include "voronoi.h"

Voronoi::Voronoi()
{

}

QList<QPair<QPair<double, double>, QPair<double, double> > > Voronoi::getAristas() {
    return this->aristas;
}

QPair<double, double> Voronoi::midPoint( QPair<QPair<double, double>, QPair<double,double> > arista) {
    QPair<double, double> pair((arista.first.first + arista.second.first) / 2.0,(arista.first.second + arista.second.second) / 2.0);
    return pair;
}

void Voronoi::agregarArista(QPair<double, double> punto1, QPair<double, double> punto2) {
    QPair<QPair<double,double>, QPair<double, double>> linea(punto1, punto2);
    this->aristas.push_back(linea);
}

void Voronoi::calcular(GrafoHistorico *grafoDelaunay){

    QList<Triangulo*> triangulos = grafoDelaunay->listarHojas();

    QPair<double, double> puntoMedioArista;
    QList<QPair<QPair<double, double>, QPair<double,double> > > aristas;
    QPair<QPair<double, double>, QPair<double, double> > arista;
    NodoGrafo * nodo1;
    NodoGrafo * nodo2;
    Triangulo * adyacente;
    QPair<double,double> punto1;
    QPair<double,double> punto2;
    Circunscripta * circunscripta;


    foreach (Triangulo * triangulo, triangulos) {
        aristas = triangulo->getAristas();
        for ( int i = 0; i < aristas.size(); i++) {
            arista = aristas.at(i);
            puntoMedioArista = this->midPoint(arista);

            grafoDelaunay->encontrarContienePunto(puntoMedioArista);

            nodo1 = grafoDelaunay->getPrimero();
            nodo2 = grafoDelaunay->getSegundo();

            adyacente = nodo1->getTriangulo();

            if ( adyacente == triangulo )
                adyacente = nodo2->getTriangulo();

            circunscripta = triangulo->getCircunscripta();

            punto1 = circunscripta->getCentro();

            circunscripta = adyacente->getCircunscripta();

            punto2 = circunscripta->getCentro();

            this->agregarArista(punto1, punto2);
        }
    }
}

void Voronoi::clear() {
    this->aristas.clear();
}

Voronoi::~Voronoi() {

}

