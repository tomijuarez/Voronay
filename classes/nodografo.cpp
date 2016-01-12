#include "nodografo.h"
#include "triangulo.h"

NodoGrafo::NodoGrafo(Triangulo * t){
    this->triangulo = t;
    this->procesado = false;
    this->sigHoja =  NULL;
    this->antHoja = NULL;
}

Triangulo * NodoGrafo::getTriangulo(){
    return this->triangulo;
}

QList<NodoGrafo*> NodoGrafo::getHijos(){
    return this->hijos;
}

void NodoGrafo::agregarHijo(NodoGrafo * n){
    this->hijos.append(n);
}

bool NodoGrafo::getProcesado() const{
    return procesado;
}

void NodoGrafo::setProcesado(bool value){
    procesado = value;
}

void NodoGrafo::clear(){
    delete this->triangulo;
    this->hijos.clear();
}

NodoGrafo::~NodoGrafo(){
}

NodoGrafo *NodoGrafo::getSigHoja() const{
    return sigHoja;
}

void NodoGrafo::setSigHoja(NodoGrafo *value){
    sigHoja = value;
}

NodoGrafo *NodoGrafo::getAntHoja() const
{
    return antHoja;
}

void NodoGrafo::setAntHoja(NodoGrafo *value)
{
    antHoja = value;
}





