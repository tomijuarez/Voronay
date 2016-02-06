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

double Voronoi::pendiente(QPair<double, double> p1, QPair<double,double> p2){
    if(p2.first - p1.first != 0){
        return ((p2.second - p1.second) /(p2.first - p1.first));
    }
    return 0.0;
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

                if(!triangulo->esVisitado(arista.first,arista.second)){

                    puntoMedioArista = this->midPoint(arista);

                    grafoDelaunay->encontrarContienePunto(puntoMedioArista);

                    nodo1 = grafoDelaunay->getPrimero();
                    nodo2 = grafoDelaunay->getSegundo();

                    if(nodo1 != NULL && nodo2 != NULL){
                        adyacente = nodo1->getTriangulo();
                        if ( adyacente == triangulo )
                            adyacente = nodo2->getTriangulo();

                        if(adyacente->contienePunto(p1) || adyacente->contienePunto(p2) || adyacente->contienePunto(p3)){
                            //el triangulo adyacente no pertenece a la triangulacion
                            //como el triangulo no sera visitado por su adyacente ya que no pertenece a la triangulacion "visitamos" de nuevo su arista
                            triangulo->esVisitado(arista.first,arista.second);
                            circunscripta = triangulo->getCircunscripta();
                            QPair<double,double> circAdyacente = adyacente->getCircunscripta()->getCentro();
                            punto1 = circunscripta->getCentro();
                            double pend = this->pendiente(circAdyacente,puntoMedioArista);
                            if(circAdyacente.first > punto1.first){
                              //hacia los positivos
                              QPair<double,double> puntoaux(70000.0, (pend * (70000.0-punto1.first))+punto1.second);
                              punto2 = puntoaux;
                            }else if(circAdyacente.first < punto1.first){
                              //hacia negativos
                              QPair<double,double> puntoaux(-70000.0, (pend * (-70000.0-punto1.first))+punto1.second);
                              punto2 = puntoaux;
                            }else{
                              //pendiente infinita en el mismo x
                              if(circAdyacente.second < punto1.second){
                                QPair<double,double> puntoaux(punto1.first,-70000.0);
                                punto2 = puntoaux;
                              }else if(circAdyacente.second < punto1.second){
                                QPair<double,double> puntoaux(punto1.first,70000.0);
                                punto2 = puntoaux;
                              }
                            }
                            //punto2 = circunscripta->getCentro();
                            if(punto1 != punto2){
                                this->agregarArista(punto1, punto2);
                            }
                        }else{
                            if(!adyacente->esVisitado(arista.first,arista.second)){
                                triangulo->esVisitado(arista.first,arista.second);
                                circunscripta = triangulo->getCircunscripta();
                                punto1 = circunscripta->getCentro();
                                circunscripta = adyacente->getCircunscripta();
                                punto2 = circunscripta->getCentro();
                                if(punto1 != punto2){
                                    this->agregarArista(punto1, punto2);

                                    Arista arista;
                                    arista.setPuntos(punto1, punto2);
                                    this->aristasVoronoi.push_back(arista);
                                 }
                              }
                           }
                      }else{qDebug() << "Voronoi: no pudo encontrar adyacente";}
               }
           }
       }
       actual = actual->getSigHoja();
  }
}

void Voronoi::clear() {
    this->aristas.clear();
}

QList<QPair<double, double> > Voronoi::getCentroides() {
    this->centroides = this->celdas.centroides(this->circuncentros, this->aristasVoronoi);
    return this->centroides;
}

Voronoi::~Voronoi() {

}

