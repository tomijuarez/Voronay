#include "grafohistorico.h"
#include "triangulo.h"
#include "nodografo.h"
#include <QList>
#include <QPair>
#include <QDebug>

GrafoHistorico::GrafoHistorico(Triangulo * t){
    this->raiz = new NodoGrafo(t);
    this->primero = NULL;
    this->segundo = NULL;
    QList<QPair<float,float> > vertices = t->getVertices();
    this->p1 = vertices.at(0);
    this->p2 = vertices.at(1);
    this->p3 = vertices.at(2);

}

bool GrafoHistorico::encontrarContienePunto(QPair<float, float> punto){
    bool encontrado = false;
    this->encontrar(this->raiz,punto,encontrado);
    if(!encontrado){
        qDebug() << "no se encontro triangulo";
    }
    return encontrado;
}

void GrafoHistorico::encontrar(NodoGrafo *nodo, QPair<float, float> punto,bool & encontrado){
    if(nodo->getHijos().count() != 0){ //no es una hoja
        QList<NodoGrafo*> hijos = nodo->getHijos();
        NodoGrafo * hijo;
        foreach (hijo, hijos) {
            if(!encontrado){
               if(hijo->getTriangulo()->tieneDentro(punto)){
                   this->encontrar(hijo,punto,encontrado);
               }
            }
            else{//ya se encontro el o los triangulos, cortamos la busqueda
                return;
            }
        }
    }
    else{ //es una hoja
        if(nodo->getTriangulo()->tieneDentro(punto)){
            if(nodo->getTriangulo()->estaEnUnLado(punto)){//esta en un lado (continua la busqueda por el otro triangulo)
                if(this->primero == NULL){
                    qDebug() << "Esta en un lado, se encontro el primero";
                    this->primero = nodo;
                    return;
                }
                else{
                    qDebug() << "Se encontro el segundo";
                    this->segundo = nodo;
                    encontrado = true;
                    return;
                }
            }
            else{//no esta en un lado, se encontro el triangulo ( finaliza la busqueda)
                qDebug() << "Se encontro el tringulo";
                this->primero =nodo;
                encontrado = true;
                return;
            }
        }
    }
}

NodoGrafo * GrafoHistorico::getPrimero()
{
    NodoGrafo * aux = this->primero;
    this->primero = NULL;
    return aux;
}

NodoGrafo * GrafoHistorico::getSegundo()
{
    NodoGrafo * aux = this->segundo;
    this->segundo = NULL;
    return aux;
}

NodoGrafo *GrafoHistorico::busquedaSelectiva(QPair<float, float> punto, NodoGrafo *nodo){
    bool useless = false;
    this->encontrar(this->raiz,punto,useless);
    NodoGrafo * n1 = this->getPrimero();
    NodoGrafo * n2 = this->getSegundo();
    if(n1 != nodo){
        return n1;
    }
    if(n2 != nodo){
        return n2;
    }
    qDebug() << "busqueda selectiva fallo";
    return NULL;
}

QList<Triangulo*> GrafoHistorico::listarHojas(){
    this->listaHojas.clear();
    qDebug() << " Listando Grafo";
    this->listar(this->raiz);
    QList<NodoGrafo *> nodos;
    NodoGrafo * nodo;
    foreach(nodo,nodos){
        nodo->setProcesado(false);
    }
    qDebug() << "La triangulacion tiene:";
    qDebug() << this->listaHojas.count();
    return this->listaHojas;
}

void GrafoHistorico::listar(NodoGrafo *nodo){
    if(nodo->getHijos().count() != 0){ //no es una hoja

        QList<NodoGrafo*> hijos = nodo->getHijos();
        NodoGrafo * hijo;
//        qDebug() << "No es hoja";
//        nodo->getTriangulo()->imprimir();
//        qDebug() << "Hijos";
//        foreach (hijo, hijos) {
//            hijo->getTriangulo()->imprimir();
//        }
        foreach (hijo, hijos) {
            this->listar(hijo);
        }
    }
    else{ //es una hoja
//        qDebug() << "Es hoja";
//        nodo->getTriangulo()->imprimir();
        if(!nodo->getProcesado()){
            if(!nodo->getTriangulo()->contienePunto(this->p1)
            && !nodo->getTriangulo()->contienePunto(this->p2)
            && !nodo->getTriangulo()->contienePunto(this->p3)){
                nodo->setProcesado(true);
                this->listaHojas.append(nodo->getTriangulo());
                nodo->getTriangulo()->imprimir();
            }else
                qDebug() << "El triangulo contiene un vertice del triangulo exterior";
        }else{
//            qDebug() << "Ya fue procesado antes";
            //nodo->setProcesado(false);
        }
    }
}

GrafoHistorico::~GrafoHistorico(){

}


