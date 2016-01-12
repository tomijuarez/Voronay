#include "voronoi.h"

Voronoi::Voronoi()
{

}

QList<QPair<QPair<double, double>, QPair<double, double> > > Voronoi::getAristas() {
    return this->aristas;
}

QList<QPair<double, double> > Voronoi::getCircuncentros(){
    return this->circuncentros;
}

QList<Circunscripta *> Voronoi::getCircunscriptas(){
    return this->circunscriptas;
}

QPair<double, double> Voronoi::midPoint( QPair<QPair<double, double>, QPair<double,double> > arista) {
    QPair<double, double> pair((arista.first.first + arista.second.first) / 2.0,(arista.first.second + arista.second.second) / 2.0);
    return pair;
}

void Voronoi::agregarArista(QPair<double, double> punto1, QPair<double, double> punto2) {
    QPair<QPair<double,double>, QPair<double, double>> linea(punto1, punto2);
    this->aristas.push_back(linea);
}

void Voronoi::calcular(GrafoHistorico * grafoDelaunay,NodoGrafo * listaTriangulos,QPair<double,double> p1,QPair<double,double> p2,QPair<double,double> p3){
    this->aristas.clear();
    this->circuncentros.clear();
    this->circunscriptas.clear();
    NodoGrafo * actual = listaTriangulos;
    Triangulo * triangulo = NULL;
    QPair<double, double> puntoMedioArista;
    QList<QPair<QPair<double, double>, QPair<double,double> > > aristas;
    QPair<QPair<double, double>, QPair<double, double> > arista;
    NodoGrafo * nodo1;
    NodoGrafo * nodo2;
    Triangulo * adyacente;
    QPair<double,double> punto1;
    QPair<double,double> punto2;
    Circunscripta * circunscripta;


    while(actual != NULL) {
        triangulo = actual->getTriangulo();
        if(triangulo->contienePunto(p1) || triangulo->contienePunto(p2) || triangulo->contienePunto(p3)){
            //qDebug() << "Voronoi: el triangulo tiene un punto del exterior";
           }
        else{
            this->circunscriptas.append(triangulo->getCircunscripta());
            this->circuncentros.append(triangulo->getCircunscripta()->getCentro());
            aristas = triangulo->getAristas();
            for ( int i = 0; i < aristas.size(); i++) {
                arista = aristas.at(i);
                puntoMedioArista = this->midPoint(arista);

                grafoDelaunay->encontrarContienePunto(puntoMedioArista);

                nodo1 = grafoDelaunay->getPrimero();
                nodo2 = grafoDelaunay->getSegundo();

                if(nodo1 != NULL && nodo2 != NULL){
                    adyacente = nodo1->getTriangulo();

                    if ( adyacente == triangulo )
                        adyacente = nodo2->getTriangulo();

                    circunscripta = triangulo->getCircunscripta();

                    punto1 = circunscripta->getCentro();

                    circunscripta = adyacente->getCircunscripta();

                    punto2 = circunscripta->getCentro();

                    this->agregarArista(punto1, punto2);
                }else{qDebug() << "Voronoi: no pudo encontrar adyacente";}
            }
           }
          actual = actual->getSigHoja();
    }
}

void Voronoi::clear() {
    this->aristas.clear();
}

Voronoi::~Voronoi() {

}

