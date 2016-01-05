#include "delaunay.h"
#include <QDebug>
#include "grafohistorico.h"
#include "nodografo.h"
#include "circunscripta.h"

Delaunay::Delaunay()
{
    this->trianguloExterior = NULL;
    this->grafoHistorico = NULL;
    this->calculada = false;
}

Delaunay::Delaunay(QList<QPair<float, float> > puntos, Triangulo * trianguloExterior) {
    QList<QPair<float, float> > puntosIniciales = trianguloExterior->getVertices();
    //Evitamos que se puede modificar el traingulo inicial desde "afuera"
    this->trianguloExterior = new Triangulo(puntosIniciales.at(0),puntosIniciales.at(1),puntosIniciales.at(2));
    this->puntos = puntos;
    //this->triangulos.append(trianguloInicial);
    this->grafoHistorico = new GrafoHistorico(trianguloExterior);
    this->calculada = false;
}

/**
 * @brief Delaunay::triangular
 * @param puntos [NUBE DE PUNTOS]
 * @return [TRIANGULACIÓN]
 */
QList<Triangulo *> Delaunay::triangular(){
    if(!this->calculada){
        if(this->trianguloExterior == NULL){
            qDebug() << " Debe setear el triangulo exterior antes de triangular";
            QList<Triangulo*> vacia;
            return vacia;
        }
        QPair<float, float> p;
        foreach (p, this->puntos) {
            qDebug() << "Insertando";
            qDebug() << p;
            this->puntosInsertados.append(p);
            this->insertarVertice(p);
        }
        this->calculada = true;
     }
        /*
        Triangulo * t;
        qDebug() << "Listando Triangulos";
        foreach(t,this->triangulos){
            t->contieneArista(par,par);
            t->getCircunscripta();
        }
        */
      return this->grafoHistorico->listarHojas();
    }

    void Delaunay::resetear()
    {
        delete this->trianguloExterior;
        this->trianguloExterior = NULL;
        this->puntosInsertados.clear();
        this->puntos.clear();
        this->grafoHistorico->clear();
        delete this->grafoHistorico;
        this->grafoHistorico = NULL;
        this->calculada = false;
    }


void Delaunay::insertarVertice(QPair<float, float> vertice) {
//    Triangulo * triangulo;
//    int contador = 0;
//    int primerTriangulo=-1;  //Posicion del primer triangulo encontrado dado el vertice este en uno de sus lados
//    int segundoTriangulo=0; //Existe la posibilidad que haya otro triangulo mas
//    bool caso1 = false;
//    bool caso2 = false;
//    Triangulo * tAux1 = NULL;
//    Triangulo * tAux2 = NULL;
//    //QPair<float,float> useless(0,0);

//    foreach(triangulo, this->triangulos) {
//      if ( triangulo->tieneDentro(vertice) ) {
//            if ( triangulo->estaEnUnLado(vertice) ) {
//                //Está sobre un lado {CASO 2}
//                if(primerTriangulo == -1){
//                   qDebug() << "Esta en un lado";
//                   qDebug() << "Primer Triangulo";
//                   //this->triangulos.at(contador)->contieneArista(useless,useless);
//                   primerTriangulo = contador;
//                }else{
//                    qDebug() << "Se encontro el adyacente";
//                    //this->triangulos.at(contador)->contieneArista(useless,useless);
//                    segundoTriangulo = contador; //Siempre hay un segundo triángulo adyacente si cae sobre un lado
//                    caso2 = true;
//                    break;
//                 }
//            }
//            else{
//                //Está dentro {CASO 1}
//                qDebug() << "Esta dentro";
//                primerTriangulo = contador;
//                caso1 = true;
//                break;
//            }
//        }
//        contador++;
//    }

//    if (caso1){
//        qDebug() << "Entrando en Caso 1";
//        tAux1 = this->triangulos.at(primerTriangulo);//Guardamos un puntero al tríangulo.
//        this->triangulos.removeAt(primerTriangulo);//Eliminamos el triangulo de la lista
//        this->generarTriangulos(tAux1,vertice);
//        delete tAux1; // Liberamos memoria
//        //Entró en el triángulo y se procesó. Fin.
//    }

//    if (caso2){
//        qDebug() << "Entrando en Caso 2";
//        tAux1 = this->triangulos.at(primerTriangulo);
//        tAux2 = this->triangulos.at(segundoTriangulo);
//        this->triangulos.removeAt(primerTriangulo);
//        this->triangulos.removeAt(segundoTriangulo - 1);
//        this->dividirTriangulos(tAux1,tAux2,vertice);
//        delete tAux1;
//        delete tAux2;
//    }
        //Utilizamos el grafo historico para encontrar el/los triangulos en los que cae el punto
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
            qDebug() << "Entrando en Caso 1";
            this->generarTriangulos(nAux1,vertice);
        }

        if (caso2){
            qDebug() << "Entrando en Caso 2";
            this->dividirTriangulos(nAux1,nAux2,vertice);
        }

        if(!caso1 && !caso2){
            qDebug() << "Error, el punto no pertenece a ningun caso";
        }

}


/**
 * @brief Delaunay::generarTriangulos {PARA EL CASO 1}
 * @param t
 * @param vertice
 * @return
 */
//void Delaunay::generarTriangulos( Triangulo * t, QPair<float, float> vertice ) {
//    qDebug() << "Generando 3 triangulos";
//    QList<QPair<float,float> > vertices = t->getVertices();
//    Triangulo * t1 = new Triangulo(vertices.at(0),vertices.at(1),vertice);
//    Triangulo * t2 = new Triangulo(vertices.at(0),vertices.at(2),vertice);
//    Triangulo * t3 = new Triangulo(vertices.at(1),vertices.at(2),vertice);
//    this->triangulos.append(t1);
//    this->triangulos.append(t2);
//    this->triangulos.append(t3);
//    this->legalizarLado(vertice,vertices.at(0),vertices.at(1),t1);
//    this->legalizarLado(vertice,vertices.at(2),vertices.at(0),t2);
//    this->legalizarLado(vertice,vertices.at(1),vertices.at(2),t3);
//    return;
//}

void Delaunay::generarTriangulos( NodoGrafo * nodo, QPair<float, float> vertice ) {
    qDebug() << "El punto cayo en";
    nodo->getTriangulo()->imprimir();
    qDebug() << "Generando 3 triangulos";
    //Partimos el triangulo en 3 usando el nuevo vertice
    QList<QPair<float,float> > vertices = nodo->getTriangulo()->getVertices();
    Triangulo * t1 = new Triangulo(vertices.at(0),vertices.at(1),vertice);
    Triangulo * t2 = new Triangulo(vertices.at(0),vertices.at(2),vertice);
    Triangulo * t3 = new Triangulo(vertices.at(1),vertices.at(2),vertice);
    qDebug() << "Triangulos nuevos:";
    t1->imprimir();
    t2->imprimir();
    t3->imprimir();
    //Aactualizamos el grafo historico
    NodoGrafo * nodoT1 = new NodoGrafo(t1);
    NodoGrafo * nodoT2 = new NodoGrafo(t2);
    NodoGrafo * nodoT3 = new NodoGrafo(t3);
    nodo->agregarHijo(nodoT1);
    nodo->agregarHijo(nodoT2);
    nodo->agregarHijo(nodoT3);
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

//void Delaunay::dividirTriangulos( Triangulo * t1, Triangulo * t2, QPair<float, float> vertice ) {
//    qDebug() << "Dividiendo Triangulos en 2";
//    QList<Triangulo*> triangulos;
//    QPair<float,float> verticeCompartido1;
//    QPair<float,float> verticeCompartido2;
//    QPair<float,float> verticeDistinto1;
//    QPair<float,float> verticeDistinto2;
//    QList<QPair<float,float> > verticesT1 = t1->getVertices();
//    QList<QPair<float,float> > verticesT2 = t2->getVertices();
//    QList<QPair<float,float> > vertices;

//    vertices.append(verticesT1);
//    vertices.append(verticesT2);
//    int encontrados = 0;

//    QPair<float,float> vertAux;
//    foreach(vertAux,vertices){
//        if (vertices.count(vertAux) > 1){
//            if (encontrados == 0){
//                encontrados++;
//                verticeCompartido1=vertAux;
//            }
//            else{
//                verticeCompartido2=vertAux;
//                break;
//            }
//       }
//    }



//    foreach(vertAux,verticesT1){
//        if (vertAux != verticeCompartido1 && vertAux != verticeCompartido2){
//            verticeDistinto1 = vertAux;
//            break;
//        }
//    }

//    foreach(vertAux,verticesT2){
//        if (vertAux != verticeCompartido1 && vertAux != verticeCompartido2){
//            verticeDistinto2 = vertAux;
//            break;
//        }
//    }

//    Triangulo * trianguloT11 = new Triangulo(verticeCompartido1,vertice,verticeDistinto1);
//    Triangulo * trianguloT12 = new Triangulo(verticeCompartido2,vertice,verticeDistinto1);
//    Triangulo * trianguloT21 = new Triangulo(verticeCompartido1,vertice,verticeDistinto2);
//    Triangulo * trianguloT22 = new Triangulo(verticeCompartido2,vertice,verticeDistinto2);

//    this->triangulos.append(trianguloT11);
//    this->triangulos.append(trianguloT12);
//    this->triangulos.append(trianguloT21);
//    this->triangulos.append(trianguloT22);
//    this->legalizarLado(vertice,verticeCompartido1,verticeDistinto1,trianguloT11);
//    this->legalizarLado(vertice,verticeCompartido2,verticeDistinto1,trianguloT12);
//    this->legalizarLado(vertice,verticeCompartido1,verticeDistinto2,trianguloT21);
//    this->legalizarLado(vertice,verticeCompartido2,verticeDistinto2,trianguloT22);
//    return;
//}

void Delaunay::dividirTriangulos( NodoGrafo * nodo1, NodoGrafo * nodo2, QPair<float, float> vertice){
    qDebug() << "El punto cayo entre";
    nodo1->getTriangulo()->imprimir();
    nodo2->getTriangulo()->imprimir();
    qDebug() << "Dividiendo Triangulos en 2";

    //Ubicamos los 2 vertices que comparten los triangulos
    QPair<float,float> verticeCompartido1;
    QPair<float,float> verticeCompartido2;
    QPair<float,float> vertAux;
    QList<QPair<float,float> > verticesT1 = nodo1->getTriangulo()->getVertices();
    QList<QPair<float,float> > verticesT2 = nodo2->getTriangulo()->getVertices();
    QList<QPair<float,float> > vertices;
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
    QPair<float,float> verticeDistinto1;
    QPair<float,float> verticeDistinto2;

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

    qDebug() << " Los vertices distintos son";
    qDebug() << verticeDistinto1;
    qDebug() << verticeDistinto2;
    //Generamos los 4 nuevos triangulos
    Triangulo * trianguloT11 = new Triangulo(verticeCompartido1,vertice,verticeDistinto1);
    Triangulo * trianguloT12 = new Triangulo(verticeCompartido2,vertice,verticeDistinto1);
    Triangulo * trianguloT21 = new Triangulo(verticeCompartido1,vertice,verticeDistinto2);
    Triangulo * trianguloT22 = new Triangulo(verticeCompartido2,vertice,verticeDistinto2);
    qDebug() << "Nuevos Triangulos";
    trianguloT11->imprimir();
    trianguloT12->imprimir();
    trianguloT21->imprimir();
    trianguloT22->imprimir();
    //Actualizamos el grafo historico
    NodoGrafo * nodoT11 = new NodoGrafo(trianguloT11);
    NodoGrafo * nodoT12 = new NodoGrafo(trianguloT12);
    NodoGrafo * nodoT21 = new NodoGrafo(trianguloT21);
    NodoGrafo * nodoT22 = new NodoGrafo(trianguloT22);
    nodo1->agregarHijo(nodoT11);
    nodo1->agregarHijo(nodoT12);
    nodo2->agregarHijo(nodoT21);
    nodo2->agregarHijo(nodoT22);
    //Legalizamos los nuevos triangulos
    this->legalizarLado(vertice,verticeCompartido1,verticeDistinto1,nodoT11);
    this->legalizarLado(vertice,verticeCompartido2,verticeDistinto1,nodoT12);
    this->legalizarLado(vertice,verticeCompartido1,verticeDistinto2,nodoT21);
    this->legalizarLado(vertice,verticeCompartido2,verticeDistinto2,nodoT22);
    return;
}

float Delaunay::determinante(QPair<float, float> punto1, QPair<float, float> punto2, QPair<float, float> punto3){
    return (  punto1.first * ( punto2.second - punto3.second )
            + punto2.first * ( punto3.second - punto1.second )
            + punto3.first * ( punto1.second - punto2.second )
            );
}

//void Delaunay::legalizarLado(QPair<float, float> puntoNuevo, QPair<float, float> vertice1, QPair<float, float> vertice2, Triangulo *t){
//    qDebug() << "Legalizando Lado";
//    qDebug() << vertice1;
//    qDebug() << vertice2;
//    bool flag = false;
//    bool legal = true;

//    Triangulo * adyacente = this->buscarAdyacente(vertice1,vertice2,t);
//    if (adyacente != NULL){
//        QList<QPair<float,float> > verticesAdyacente = adyacente->getVertices();
//        QPair<float,float> vertAux;
//        QPair<float,float> verticeDistintoAdyacente;

//        foreach(vertAux,verticesAdyacente){
//            if (vertAux != vertice1 && vertAux != vertice2){
//                verticeDistintoAdyacente = vertAux;
//                qDebug() << "Vertice Distinto";
//                qDebug() << vertAux;
//                break;
//            }
//        }

//        if(!flag){
//            //Probar caso 2
//        }

//        if(!flag){
//            //Probar caso 3
//        }

//     }else{
//        flag = true; //La arista pertenece al triangulo exterior CASO 1
//     }

//     if(!flag){ //Caso normal
//        QPair<float,float> p;
//        Circunscripta * c = t->getCircunscripta();
//        foreach(p,this->puntosInsertados){
//            if(c->estaDentro(p)){
//                legal = false;
//                break;
//            }
//        }
//        delete c;
//     }

//     if (!legal){
//        // FLIP ARISTA
//        }

//}

void Delaunay::legalizarLado(QPair<float, float> puntoNuevo, QPair<float, float> vertice1, QPair<float, float> vertice2, NodoGrafo * nodo){
    //Verificamos que el lado en cuestion no pertenece al triangulo exterior
       qDebug() << "Legalizando";
       nodo->getTriangulo()->imprimir();
       if(!this->trianguloExterior->contieneArista(vertice1,vertice2)){
        //Encontramos el Triangulo adyacente en el history graph
        //para esto utilizamos el punto medio del lado compartido
        //solo dos triangulo comparten este punto, el triangulo en cuestion y su adyacente
        QPair<float, float> puntoMedio((vertice1.first+vertice2.first)/2,(vertice1.second+vertice2.second)/2);
        NodoGrafo * adyacente = this->grafoHistorico->busquedaSelectiva(puntoMedio,nodo);
        if (adyacente == NULL){
            qDebug() << "adyacente no encontrado";
        }else{
            qDebug() << "adyacente encontrado";
            adyacente->getTriangulo()->imprimir();
            //encontramos el adyacente, ahora ubicamos el vertice que no comparten para verificar que no caiga
            //dentro de la circunferencia circunscripta
                   QList<QPair<float,float> > verticesAdyacente = adyacente->getTriangulo()->getVertices();
                   QPair<float,float> vertAux;
                   QPair<float,float> verticeDistintoAdyacente;

                   foreach(vertAux,verticesAdyacente){
                       if (vertAux != vertice1 && vertAux != vertice2){
                           verticeDistintoAdyacente = vertAux;
                           qDebug() << "Vertice Distinto";
                           qDebug() << vertAux;
                           break;
                       }
                   }

                   //verificamos la regla de la circunferencia vacia
                   if(nodo->getTriangulo()->getCircunscripta()->estaDentro(verticeDistintoAdyacente)){
                       qDebug() << "Circunferencia no vacia";
                   //si no se cumple, debemos hacer flip a la arista
                   //esto implica unir el punto insertado con el vertice distinto del adyacente
                   //Creamos los triangulos nuevos
                       Triangulo * T1 = new Triangulo(puntoNuevo,vertice1,verticeDistintoAdyacente);
                       Triangulo * T2 = new Triangulo(puntoNuevo,vertice2,verticeDistintoAdyacente);
                       qDebug() << "Nuevos Triangulos";
                       T1->imprimir();
                       T2->imprimir();
                   //Actualizamos el History graph
                       NodoGrafo * nodoT1 = new NodoGrafo(T1);
                       NodoGrafo * nodoT2 = new NodoGrafo(T2);
                       adyacente->agregarHijo(nodoT1);
                       adyacente->agregarHijo(nodoT2);
                       nodo->agregarHijo(nodoT1);
                       nodo->agregarHijo(nodoT2);
                   //Hay que legalizar las nuevas aristas que no contienen al punto que se inserto
                       this->legalizarLado(puntoNuevo,vertice1,verticeDistintoAdyacente,nodoT1);
                       this->legalizarLado(puntoNuevo,vertice2,verticeDistintoAdyacente,nodoT2);
                   }else{
                       qDebug() << "Circunferencia vacia";
                   }
        }
       }else{
           qDebug() << "El lado pertenece al traingulo exterior Legal!";
       }
}
Triangulo *Delaunay::getTrianguloExterior() const{
    return this->trianguloExterior;
}

void Delaunay::setTrianguloExterior(Triangulo *value){
   if(!calculada){
        this->trianguloExterior = value;
        this->grafoHistorico = new GrafoHistorico(value);
   }else{qDebug() << "Debe resetear la triangulacion antes de cambiar el triangulo exterior";}
}

QList<QPair<float, float> > Delaunay::getPuntos() const
{
    return this->puntos;
}

void Delaunay::setPuntos(const QList<QPair<float, float> > &value){
    if(!calculada){
        this->puntos = value;
    }else{qDebug() << "Debe resetear la triangulacion antes de cambiar el triangulo exterior";}
}


//Triangulo *Delaunay::buscarAdyacente(QPair<float, float> punto1, QPair<float, float> punto2, Triangulo *t1){
//    qDebug() << "Buscando Adyacente";
//    Triangulo * t = NULL;
//    foreach(t,this->triangulos){
//        if(t->contieneArista(punto1,punto2) && t != t1){
//            qDebug() << "Adyacente Encontrado";
//            return t;
//        }
//    }
//    qDebug() << "Adyacente no encontrado";
//    return NULL;
//}

Delaunay::~Delaunay() {
    this->resetear();
}

