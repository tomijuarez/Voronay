#include "delaunay.h"
#include <QDebug>
#include "grafohistorico.h"
#include "nodografo.h"
#include "circunscripta.h"

Delaunay::Delaunay()
{
    this->trianguloExterior = NULL;
    this->grafoHistorico = NULL;
    this->listaTriangulos = NULL;
    this->calculada = false;
}

/**
 * @brief Delaunay::triangular
 * @param puntos [NUBE DE PUNTOS]
 * @return [TRIANGULACIÓN]
 */
void Delaunay::triangular(){
    if(!this->calculada){
        if(this->trianguloExterior == NULL){
            qDebug() << "Delaunay: Debe setear el triangulo exterior antes de triangular";
            return;
        }
        QPair<double, double> p;
        foreach (p, this->puntos) {
            this->puntosInsertados.append(p);
            this->insertarVertice(p);
        }
        this->calculada = true;
     }else{qDebug() << "Delaunay: Ya se encuentra triangulada";}
      return;
    }

 void Delaunay::resetear(){
      if(this->trianguloExterior != NULL){
        this->trianguloExterior = NULL;
        this->grafoHistorico->clear();
        this->listaTriangulos = NULL;
        delete this->grafoHistorico;
        this->grafoHistorico = NULL;
       }
      this->puntosInsertados.clear();
      this->puntos.clear();
      this->calculada = false;
    }


void Delaunay::insertarVertice(QPair<double, double> vertice) {
        //Utilizamos el grafo historico para encontrar el/los triangulos en los que cae el punto
        //qDebug() << "Delaunay: Insertando";
        //qDebug() << vertice;
        NodoGrafo * nAux1 = NULL;
        NodoGrafo * nAux2 = NULL;
        this->grafoHistorico->encontrarContienePunto(vertice);
        nAux1=this->grafoHistorico->getPrimero();
        nAux2=this->grafoHistorico->getSegundo();
        bool caso1 = false;
        bool caso2 = false;
        //Si se encontraron 2 triangulos el punto cae en un lado
        if(nAux1 != NULL && nAux2 != NULL){
            caso2=true;
        }
        //Si se encontro 1 triangulo el punto cae dentro del mismo
        else if(nAux1 != NULL){
            caso1 = true;
        }
        if (caso1){
           //qDebug() << "Delaunay: Entrando en Caso 1";
            this->generarTriangulos(nAux1,vertice);
        }

        if (caso2){
            //qDebug() << "Delaunay: Entrando en Caso 2";
            this->dividirTriangulos(nAux1,nAux2,vertice);
        }

        if(!caso1 && !caso2){
            qDebug() << "Delaunay: Error, el punto no pertenece a ningun caso";
        }

}


/**
 * @brief Delaunay::generarTriangulos {PARA EL CASO 1}
 * @param t
 * @param vertice
 * @return
 */

void Delaunay::generarTriangulos( NodoGrafo * nodo, QPair<double, double> vertice ) {
    //qDebug() << "Delaunay: El punto cayo en";
    //nodo->getTriangulo()->imprimir();
    //qDebug() << "Generando 3 triangulos";
    //Partimos el triangulo en 3 usando el nuevo vertice
    QList<QPair<double,double> > vertices = nodo->getTriangulo()->getVertices();
    Triangulo * t1 = new Triangulo(vertices.at(0),vertices.at(1),vertice);
    Triangulo * t2 = new Triangulo(vertices.at(0),vertices.at(2),vertice);
    Triangulo * t3 = new Triangulo(vertices.at(1),vertices.at(2),vertice);
    //qDebug() << "Triangulos nuevos:";
    //t1->imprimir();
    //t2->imprimir();
    //t3->imprimir();
    //Aactualizamos el grafo historico
    //Agregamos nuevos hijos
    NodoGrafo * nodoT1 = new NodoGrafo(t1);
    NodoGrafo * nodoT2 = new NodoGrafo(t2);
    NodoGrafo * nodoT3 = new NodoGrafo(t3);
    nodo->agregarHijo(nodoT1);
    nodo->agregarHijo(nodoT2);
    nodo->agregarHijo(nodoT3);
    //Mantenemos la lista de hojas
    nodoT1->setSigHoja(nodoT2);
    nodoT2->setSigHoja(nodoT3);
    nodoT2->setAntHoja(nodoT1);
    nodoT3->setAntHoja(nodoT2);
    NodoGrafo * siguiente = nodo->getSigHoja();
    if(siguiente != NULL){
        nodoT3->setSigHoja(siguiente);
        siguiente->setAntHoja(nodoT3);
    }
    if(this->listaTriangulos == nodo  || this->listaTriangulos == NULL){
        this->listaTriangulos = nodoT1;
    }else{
        NodoGrafo * apuntador = nodo->getAntHoja();
        nodoT1->setAntHoja(apuntador);
        apuntador->setSigHoja(nodoT1);
     }
    //Legalizamos los nuevos triangulos
    this->legalizarLado(vertice,vertices.at(0),vertices.at(1),nodoT1);
    this->legalizarLado(vertice,vertices.at(2),vertices.at(0),nodoT2);
    this->legalizarLado(vertice,vertices.at(1),vertices.at(2),nodoT3);
    return;
}

    /**
     *1. El punto que se está insertando es pr, y pi pj es la arista de T a la que puede ser necesario hacer un flip
2. Se comprueba por las propiedades de las Triangulaciones de Delaunay anteriormente vista si pi pj es ilegal
3.     Si es ilegal
           Sea pi pj pk el triángulo adyacente a pr pi pj compartiendo la arista pi pj
4.        Se reemplaza pi pj por pr pk
5.        LEGALIZA_LADO (pr,pi pk, T)
6.        LEGALIZA_LADO (pr,pk pj, T)
     */


/**
 * @brief Delaunay::generarTriangulos {CASO 2}
 * @param t1
 * @param t2
 * @param vertice
 * @return
 */


void Delaunay::dividirTriangulos( NodoGrafo * nodo1, NodoGrafo * nodo2, QPair<double, double> vertice){
    //qDebug() << "Delaunay: El punto cayo entre";
    //nodo1->getTriangulo()->imprimir();
    //nodo2->getTriangulo()->imprimir();
    //qDebug() << "Dividiendo Triangulos en 2";

    //Ubicamos los 2 vertices que comparten los triangulos
    QPair<double,double> verticeCompartido1;
    QPair<double,double> verticeCompartido2;
    QPair<double,double> vertAux;
    QList<QPair<double,double> > verticesT1 = nodo1->getTriangulo()->getVertices();
    QList<QPair<double,double> > verticesT2 = nodo2->getTriangulo()->getVertices();
    QList<QPair<double,double> > vertices;
    vertices.append(verticesT1);
    vertices.append(verticesT2);
    int encontrados = 0;

    foreach(vertAux,vertices){
        if (vertices.count(vertAux) > 1){
            if (encontrados == 0){
                encontrados++;
                verticeCompartido1=vertAux;
            }
            else{
                verticeCompartido2=vertAux;
                break;
            }
       }
    }

    //Ubicamos el vertice que no comparte un triangulo con el otro para cada triangulo
    QPair<double,double> verticeDistinto1;
    QPair<double,double> verticeDistinto2;

    foreach(vertAux,verticesT1){
        if (vertAux != verticeCompartido1 && vertAux != verticeCompartido2){
            verticeDistinto1 = vertAux;
            break;
        }
    }

    foreach(vertAux,verticesT2){
        if (vertAux != verticeCompartido1 && vertAux != verticeCompartido2){
            verticeDistinto2 = vertAux;
            break;
        }
    }

    //qDebug() << " Los vertices distintos son";
    //qDebug() << verticeDistinto1;
    //qDebug() << verticeDistinto2;
    //Generamos los 4 nuevos triangulos
    Triangulo * trianguloT11 = new Triangulo(verticeCompartido1,vertice,verticeDistinto1);
    Triangulo * trianguloT12 = new Triangulo(verticeCompartido2,vertice,verticeDistinto1);
    Triangulo * trianguloT21 = new Triangulo(verticeCompartido1,vertice,verticeDistinto2);
    Triangulo * trianguloT22 = new Triangulo(verticeCompartido2,vertice,verticeDistinto2);
    //qDebug() << "Nuevos Triangulos";
    //trianguloT11->imprimir();
    //trianguloT12->imprimir();
    //trianguloT21->imprimir();
    //trianguloT22->imprimir();
    //Actualizamos el grafo historico
    //Insertamos Hijos
    NodoGrafo * nodoT11 = new NodoGrafo(trianguloT11);
    NodoGrafo * nodoT12 = new NodoGrafo(trianguloT12);
    NodoGrafo * nodoT21 = new NodoGrafo(trianguloT21);
    NodoGrafo * nodoT22 = new NodoGrafo(trianguloT22);
    nodo1->agregarHijo(nodoT11);
    nodo1->agregarHijo(nodoT12);
    nodo2->agregarHijo(nodoT21);
    nodo2->agregarHijo(nodoT22);
    //Actualizamos lista de hojas nodo1
    nodoT11->setSigHoja(nodoT12);
    nodoT12->setAntHoja(nodoT11);
    NodoGrafo * siguiente = nodo1->getSigHoja();
    if(siguiente != NULL){
        nodoT12->setSigHoja(siguiente);
        siguiente->setAntHoja(nodoT12);
    }
    if(this->listaTriangulos == nodo1 || this->listaTriangulos == NULL){
        this->listaTriangulos = nodoT11;
    }else{
        NodoGrafo * apuntador = nodo1->getAntHoja();
        nodoT11->setAntHoja(apuntador);
        apuntador->setSigHoja(nodoT11);
      }
    //Actualizamos lista de hojas nodo2
    nodoT21->setSigHoja(nodoT22);
    nodoT22->setAntHoja(nodoT21);
    siguiente = nodo2->getSigHoja();
    nodoT22->setSigHoja(siguiente);
    siguiente->setAntHoja(nodoT22);
    if(this->listaTriangulos == nodo2 || this->listaTriangulos == NULL){
        this->listaTriangulos = nodoT21;
    }else{
        NodoGrafo * apuntador = nodo2->getAntHoja();
        nodoT21->setAntHoja(apuntador);
        apuntador->setSigHoja(nodoT21);
      }
    //Legalizamos los nuevos triangulos
    this->legalizarLado(vertice,verticeCompartido1,verticeDistinto1,nodoT11);
    this->legalizarLado(vertice,verticeCompartido2,verticeDistinto1,nodoT12);
    this->legalizarLado(vertice,verticeCompartido1,verticeDistinto2,nodoT21);
    this->legalizarLado(vertice,verticeCompartido2,verticeDistinto2,nodoT22);
    return;
}

double Delaunay::determinante(QPair<double, double> punto1, QPair<double, double> punto2, QPair<double, double> punto3){
    return (  punto1.first * ( punto2.second - punto3.second )
            + punto2.first * ( punto3.second - punto1.second )
            + punto3.first * ( punto1.second - punto2.second )
            );
}

void Delaunay::legalizarLado(QPair<double, double> puntoNuevo, QPair<double, double> vertice1, QPair<double, double> vertice2, NodoGrafo * nodo){
    //Verificamos que el lado en cuestion no pertenece al triangulo exterior
       //qDebug() << "Delaunay: Legalizando";
       //nodo->getTriangulo()->imprimir();
       //qDebug() << "Delaunay: Arista";
       //qDebug() << vertice1;
       //qDebug() << vertice2;
       if(!this->trianguloExterior->contieneArista(vertice1,vertice2)){
        //Encontramos el Triangulo adyacente en el history graph
        //para esto utilizamos el punto medio del lado compartido
        //solo dos triangulo comparten este punto, el triangulo en cuestion y su adyacente
        double p1 = (vertice1.first+vertice2.first)/2.0;
        double p2 = (vertice1.second+vertice2.second)/2.0;
        QPair<double, double> puntoMedio(p1,p2);
        NodoGrafo * adyacente = this->grafoHistorico->busquedaSelectiva(puntoMedio,nodo);
        if(!nodo->getTriangulo()->estaEnUnLado(puntoMedio)){
            qDebug() << "ERROR double GOING WRONG";
        }
        this->grafoHistorico->encontrarContienePunto(puntoMedio);
        if (adyacente == NULL){
            qDebug() << "Delaunay: adyacente no encontrado";
        }else{
            //qDebug() << "Delaunay: adyacente encontrado";
            //adyacente->getTriangulo()->imprimir();
            //encontramos el adyacente, ahora ubicamos el vertice que no comparten para verificar que no caiga
            //dentro de la circunferencia circunscripta
                   QList<QPair<double,double> > verticesAdyacente = adyacente->getTriangulo()->getVertices();
                   QPair<double,double> vertAux;
                   QPair<double,double> verticeDistintoAdyacente;

                   foreach(vertAux,verticesAdyacente){
                       if (vertAux != vertice1 && vertAux != vertice2){
                           verticeDistintoAdyacente = vertAux;
                           ////qDebug() << "Vertice Distinto";
                           ////qDebug() << vertAux;
                           break;
                       }
                   }

                   //verificamos la regla de la circunferencia vacia
                   if(nodo->getTriangulo()->getCircunscripta()->estaDentro(verticeDistintoAdyacente)){
                       //qDebug() << "Delaunay: Circunferencia no vacia";
                   //si no se cumple, debemos hacer flip a la arista
                   //esto implica unir el punto insertado con el vertice distinto del adyacente
                   //Creamos los triangulos nuevos
                       Triangulo * T1 = new Triangulo(puntoNuevo,vertice1,verticeDistintoAdyacente);
                       Triangulo * T2 = new Triangulo(puntoNuevo,vertice2,verticeDistintoAdyacente);
                       //qDebug() << "Nuevos Triangulos";
                       //T1->imprimir();
                       //T2->imprimir();
                   //Actualizamos el History graph
                   //Actualizamos los hijos
                       NodoGrafo * nodoT1 = new NodoGrafo(T1);
                       NodoGrafo * nodoT2 = new NodoGrafo(T2);
                       adyacente->agregarHijo(nodoT1);
                       adyacente->agregarHijo(nodoT2);
                       nodo->agregarHijo(nodoT1);
                       nodo->agregarHijo(nodoT2);
                    //Actualizamos la lista de hojas
                    //nodo
                       NodoGrafo * siguiente = nodo->getSigHoja();
                       if(siguiente != NULL){
                           siguiente->setAntHoja(nodoT1);
                       }
                       nodoT1->setSigHoja(nodo->getSigHoja());
                       if(nodo == this->listaTriangulos){
                           this->listaTriangulos = nodoT1;
                       }else{
                           NodoGrafo * anterior = nodo->getAntHoja();
                           nodoT1->setAntHoja(anterior);
                           anterior->setSigHoja(nodoT1);
                       }
                    //adyacente
                       siguiente = adyacente->getSigHoja();
                       if(siguiente != NULL){
                           siguiente->setAntHoja(nodoT2);
                       }
                       nodoT2->setSigHoja(adyacente->getSigHoja());
                       if(adyacente == this->listaTriangulos){
                           this->listaTriangulos = nodoT2;
                       }else{
                           NodoGrafo * anterior2 = adyacente->getAntHoja();
                           nodoT2->setAntHoja(anterior2);
                           anterior2->setSigHoja(nodoT2);
                       }
                   //Hay que legalizar las nuevas aristas que no contienen al punto que se inserto
                       this->legalizarLado(puntoNuevo,vertice1,verticeDistintoAdyacente,nodoT1);
                       this->legalizarLado(puntoNuevo,vertice2,verticeDistintoAdyacente,nodoT2);
                   }else{
                       //qDebug() << "Delaunay: Circunferencia vacia";
                   }
        }
       }else{
           //qDebug() << "Delaunay: El lado pertenece al traingulo exterior Legal!";
       }
}

NodoGrafo *Delaunay::getListaTriangulos() const
{
    return listaTriangulos;
}

QPair<double, double> Delaunay::getP3() const
{
    return p3;
}

QPair<double, double> Delaunay::getP2() const
{
    return p2;
}

QPair<double, double> Delaunay::getP1() const
{
    return p1;
}
GrafoHistorico *Delaunay::getGrafoHistorico() const
{
    return grafoHistorico;
}

Triangulo *Delaunay::getTrianguloExterior() const{
    return this->trianguloExterior;
}

void Delaunay::setTrianguloExterior(Triangulo *value){
    if(!calculada){
        QList<QPair<double,double> > vertices = value->getVertices();
        this->trianguloExterior = new Triangulo(vertices.at(0),vertices.at(1),vertices.at(2));
        this->p1 = vertices.at(0);
        this->p2 = vertices.at(1);
        this->p3 = vertices.at(2);
        this->grafoHistorico = new GrafoHistorico(this->trianguloExterior);
   }else{qDebug() << "Delaunay: Debe resetear la triangulacion antes de cambiar el triangulo exterior";}
}

QList<QPair<double, double> > Delaunay::getPuntos() const
{
    return this->puntos;
}

void Delaunay::agregarPunto(QPair<double, double> punto){
    if(this->calculada == false){
        qDebug() << "Delaunay: Primero debe calcular la triangulacion una vez antes de agregar mas puntos";
    }
    else{
        this->insertarVertice(punto);
        qDebug() << "Se calculo";
    }
}

void Delaunay::setPuntos(const QList<QPair<double, double> > &value){
    if(!calculada){
        this->puntos = value;
    }else{qDebug() << "Delaunay: Debe resetear la triangulacion antes de cambiar el triangulo exterior";}
}

Delaunay::~Delaunay() {
    this->resetear();
}

