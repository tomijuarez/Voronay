#include "triangulo.h"
#include <QDebug>

Triangulo::Triangulo() { }

Triangulo::Triangulo(QPair<double, double> punto1, QPair<double, double> punto2, QPair<double, double> punto3){
    this->definirPuntos(punto1, punto2, punto3);
}

void Triangulo::definirPuntos(QPair<double, double> punto1, QPair<double, double> punto2, QPair<double, double> punto3) {
    this->punto1 = punto1;
    this->punto2 = punto2;
    this->punto3 = punto3;
}

double Triangulo::area(QPair<double, double> punto1, QPair<double, double> punto2, QPair<double, double> punto3) {
    return fabs(
        (
                punto1.first * ( punto2.second - punto3.second )
            +   punto2.first * ( punto3.second - punto1.second )
            +   punto3.first * ( punto1.second - punto2.second )
        ) / 2.0
    );
}

bool Triangulo::tieneDentro(QPair<double, double> punto) {
    double A = this->area(this->punto1, this->punto2, this->punto3);
    double A1 = this->area(punto, this->punto2, this->punto3);
    double A2 = this->area(this->punto1, punto, this->punto3);
    double A3 = this->area(this->punto1, this->punto2, punto);

    if(A == (A1 + A2 + A3)){
        return true;
    }
    return false;
}

bool Triangulo::estaEnUnLado(QPair<double, double> punto) {
    double A1 = this->area(punto, this->punto2, this->punto3);
    double A2 = this->area(this->punto1, punto, this->punto3);
    double A3 = this->area(this->punto1, this->punto2, punto);

    return (A1 == 0 || A2 == 0 || A3 == 0);
}

bool Triangulo::contieneArista(QPair<double, double> punto1, QPair<double, double> punto2){
    return (this->contienePunto(punto1) && this->contienePunto(punto2));
}

bool Triangulo::contienePunto(QPair<double, double> punto){
    bool resultado = ((punto.first == this->punto1.first && punto.second == this->punto1.second)
            || (punto.first == this->punto2.first && punto.second == this->punto2.second)
            || (punto.first == this->punto3.first && punto.second == this->punto3.second));
    return resultado;
}

QList<QPair<double,double> > Triangulo::getVertices(){
    QList<QPair<double, double> > resultado;
    resultado.append(this->punto1);
    resultado.append(this->punto2);
    resultado.append(this->punto3);
    return resultado;
}

QList<QPair<QPair<double,double>,QPair<double,double> > > Triangulo::getAristas(){
    QList<QPair<QPair<double,double>,QPair<double,double> > > resultado;
    QPair<QPair<double,double>,QPair<double,double> > arista1(this->punto1,this->punto2);
    QPair<QPair<double,double>,QPair<double,double> > arista2(this->punto1,this->punto3);
    QPair<QPair<double,double>,QPair<double,double> > arista3(this->punto2,this->punto3);
    resultado.append(arista1);
    resultado.append(arista2);
    resultado.append(arista3);
    return resultado;
}

Circunscripta * Triangulo::getCircunscripta(){
    Circunscripta * circunscripta = new Circunscripta(this->punto1,this->punto2,this->punto3);
    return circunscripta;
}

void Triangulo::imprimir()
{
    qDebug() << "Triangulo:";
    qDebug() << this->punto1;
    qDebug() << this->punto2;
    qDebug() << this->punto3;
}

Triangulo::~Triangulo() { }

