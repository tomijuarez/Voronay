#include "triangulo.h"
#include <QDebug>

Triangulo::Triangulo() { }

Triangulo::Triangulo(QPair<float, float> punto1, QPair<float, float> punto2, QPair<float, float> punto3){
    this->definirPuntos(punto1, punto2, punto3);
}

void Triangulo::definirPuntos(QPair<float, float> punto1, QPair<float, float> punto2, QPair<float, float> punto3) {
    this->punto1 = punto1;
    this->punto2 = punto2;
    this->punto3 = punto3;
}

float Triangulo::area(QPair<float, float> punto1, QPair<float, float> punto2, QPair<float, float> punto3) {
    return abs(
        (
                punto1.first * ( punto2.second - punto3.second )
            +   punto2.first * ( punto3.second - punto1.second )
            +   punto3.first * ( punto1.second - punto2.second )
        ) / 2.0
    );
}

bool Triangulo::tieneDentro(QPair<float, float> punto) {
    float A = this->area(this->punto1, this->punto2, this->punto3);
    float A1 = this->area(punto, this->punto2, this->punto3);
    float A2 = this->area(this->punto1, punto, this->punto3);
    float A3 = this->area(this->punto1, this->punto2, punto);

    return (A == (A1 + A2 + A3));

}

bool Triangulo::estaEnUnLado(QPair<float, float> punto) {
    float A1 = this->area(punto, this->punto2, this->punto3);
    float A2 = this->area(this->punto1, punto, this->punto3);
    float A3 = this->area(this->punto1, this->punto2, punto);

    return (A1 == 0 || A2 == 0 || A3 == 0);
}

bool Triangulo::contieneArista(QPair<float, float> punto1, QPair<float, float> punto2){
    return (this->contienePunto(punto1) && this->contienePunto(punto2));
}

bool Triangulo::contienePunto(QPair<float, float> punto){
    bool resultado = ((punto.first == this->punto1.first && punto.second == this->punto1.second)
            || (punto.first == this->punto2.first && punto.second == this->punto2.second)
            || (punto.first == this->punto3.first && punto.second == this->punto3.second));
    return resultado;
}

QList<QPair<float,float> > Triangulo::getVertices(){
    QList<QPair<float, float> > resultado;
    resultado.append(this->punto1);
    resultado.append(this->punto2);
    resultado.append(this->punto3);
    return resultado;
}

QList<QPair<QPair<float,float>,QPair<float,float> > > Triangulo::getAristas(){
    QList<QPair<QPair<float,float>,QPair<float,float> > > resultado;
    QPair<QPair<float,float>,QPair<float,float> > arista1(this->punto1,this->punto2);
    QPair<QPair<float,float>,QPair<float,float> > arista2(this->punto1,this->punto3);
    QPair<QPair<float,float>,QPair<float,float> > arista3(this->punto2,this->punto3);
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

