#include "circunscripta.h"
#include <math.h>
#include <QDebug>
/*
Circunscripta::Circunscripta(QPair<double, double> punto1, QPair<double, double> punto2, QPair<double, double> punto3) {
    double bc = (pow(punto1.first, 2) + pow(punto1.first, 2) - pow(punto2.first, 2) + pow(punto2.second, 2))/2.0;
    double cd = (pow(punto2.first, 2) + pow(punto2.first, 2) - pow(punto3.first, 2) + pow(punto3.second, 2))/2.0;

    double det = (punto1.first - punto2.first)*(punto2.second - punto3.second)-(punto2.first - punto3.first)*(punto1.second - punto2.second);

    if (abs(det) < 1.0e-6) {
        this->centro.first = this->centro.second = 1.0;
        return;
    }

    det = 1/det;

    this->centro.first = (bc*(punto2.second - punto3.second) - cd*(punto1.second - punto2.second))*det;
    this->centro.second = (cd*(punto1.first - punto2.first) - bc*(punto2.first - punto3.first))*det;

    this->radio = sqrt(pow(this->centro.first - punto1.first, 2) + pow(this->centro.second - punto1.second,2));
}
*/

Circunscripta::Circunscripta(QPair<double, double> punto1, QPair<double, double> punto2, QPair<double, double> punto3) {
      //qDebug() << "Calculando Circuncentro";
      //qDebug() <<"Punto1";
      //qDebug() << punto1;
      //qDebug() << "Punto2";
      //qDebug() << punto2;
      //qDebug() << "Punto3";
      //qDebug() << punto3;

      QPair<double,double> medio12 = this->medio(punto1, punto2);
      QPair<double,double> medio13 = this->medio(punto1, punto3);
      QPair<double,double> medio23 = this->medio(punto2, punto3);


      //qDebug() << "Medio12";
      //qDebug() << medio12;
      //qDebug() << "Medio13";
      //qDebug() << medio13;
      //qDebug() << "Medio23";
      //qDebug() << medio23;

      double pendienteM12 = this->pendienteMediatriz(punto1,punto2);
      double pendienteM13 = this->pendienteMediatriz(punto1,punto3);
      double pendienteM23 = this->pendienteMediatriz(punto2,punto3);


      //qDebug() << "Pendiente M12";
      //qDebug() << pendienteM12;
      //qDebug() << "Pendiente M13";
      //qDebug() << pendienteM13;
      //qDebug() << "Pendiente M23";
      //qDebug() << pendienteM23;

      double b12 = -(medio12.first * pendienteM12) + medio12.second;
      double b13 = -(medio13.first * pendienteM13) + medio13.second;
      double b23 = -(medio23.first * pendienteM23) + medio23.second;

      //qDebug() << "B12";
      //qDebug() << b12;
      //qDebug() << "B13";
      //qDebug() << b13;
      //qDebug() << "B23";
      //qDebug() << b23;

      if(pendienteM12 != 0.0 && pendienteM13 != 0.0){
          this->centro = this->interseccion(pendienteM12,pendienteM13,b12,b13);
      }else if(pendienteM12 != 0.0 && pendienteM23 != 0.0){
          this->centro = this->interseccion(pendienteM12,pendienteM23,b12,b23);
      }else if(pendienteM13 != 0.0 && pendienteM23 != 0.0){
          this->centro = this->interseccion(pendienteM13,pendienteM23,b13,b23);
      }else{
          qDebug() << "No se pudo calcular el circuncentro";
          this->centro.first = 0.0;
          this->centro.second = 0.0;
          this->radio = 0.0;
          return;
      }

      double radio = sqrt(pow(centro.first-punto1.first,2)+pow(centro.second-punto1.second,2));
      this->radio = radio;

      //qDebug() << "Circuncentro";
      //qDebug() << this->centro;
      //qDebug() << "Radio";
      //qDebug() << this->radio;
}



Circunscripta::~Circunscripta() { }

QPair<double, double> Circunscripta::getCentro() const {
    return this->centro;
}

double Circunscripta::getRadio() const {
    return this->radio;
}

double Circunscripta::pendienteMediatriz(QPair<double,double> punto1, QPair<double,double> punto2){
    double resultado = 0.0;

    if((punto2.first != punto1.first) && (punto2.second != punto1.second)){
      resultado = -(1/((punto2.second - punto1.second)/(punto2.first-punto1.first)));
    }

    return resultado;
}

QPair<double,double> Circunscripta::medio(QPair<double,double> punto1, QPair<double,double> punto2){
    QPair<double,double> resultado;
    resultado.first = (punto1.first+punto2.first)/2.0;
    resultado.second = (punto1.second+punto2.second)/2.0;
    return resultado;
}

QPair<double,double> Circunscripta::interseccion(double m1, double m2, double b1, double b2){
    double x;
    double y;
    QPair<double,double> resultado;

    x = (b2-b1)/(m1-m2);
    y = (m1 * x) + b1;

    resultado.first = x;
    resultado.second = y;
    return resultado;
}

bool Circunscripta::estaDentro(QPair<double, double> punto) const {
    return ( (pow (punto.first - this->centro.first, 2) + pow (punto.second - this->centro.second, 2)) < pow(this->radio,2));
}
