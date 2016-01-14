#include "arista.h"

Arista::Arista() {

}

void Arista::setPuntos(QPair<double,double> inicio, QPair<double,double> fin) {
    this->inicio = inicio;
    this->fin = fin;
}

QPair<double,double> Arista::getInicio() {
    return this->inicio;
}

QPair<double,double> Arista::getFin() {
    return this->fin;
}
