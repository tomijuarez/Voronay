#ifndef DELAUNAY_H
#define DELAUNAY_H

#include <QList>
#include <QPair>
#include "triangulo.h"
#include "grafohistorico.h"
#include "nodografo.h"

class Delaunay {
public:
    Delaunay();
    Delaunay(QList<QPair<double, double> > puntos, Triangulo *trianguloExterior);
    ~Delaunay();
    void triangular();
    void resetear();
    QList<QPair<double, double> > getPuntos() const;
    void agregarPunto(QPair<double,double> punto);
    void setPuntos(const QList<QPair<double, double> > &value);

    Triangulo *getTrianguloExterior() const;
    void setTrianguloExterior(Triangulo *value);

    //Para utilizar con Voronoi
    //(Muy complejo crear copia del objeto, no utilizar funcion resetear() desde fuera
    GrafoHistorico *getGrafoHistorico() const;

    QPair<double, double> getP1() const;

    QPair<double, double> getP2() const;

    QPair<double, double> getP3() const;

    NodoGrafo *getListaTriangulos() const;

private:
    void insertarVertice(QPair<double, double> punto);
    void generarTriangulos(NodoGrafo * nodo, QPair<double, double> vertice );
    bool esLegal(QPair<double, double> punto1, QPair<double, double> punto2) const;
    void dividirTriangulos( NodoGrafo * nodo1, NodoGrafo * nodo2, QPair<double, double> vertice);
    double determinante(QPair<double, double> punto1, QPair<double, double> punto2,QPair<double, double> punto3);
    void legalizarLado(QPair<double, double> puntoNuevo, QPair<double, double> vertice1, QPair<double, double> vertice2, NodoGrafo * nodo);

    /**
     * Estructuras.
     */
    GrafoHistorico * grafoHistorico;
    QList<QPair<double,double> > puntos;
    QList<QPair<double, double> > puntosInsertados;
    Triangulo * trianguloExterior;

    bool calculada;
    QPair<double,double> p1;
    QPair<double,double> p2;
    QPair<double,double> p3;
    NodoGrafo * listaTriangulos;
};

#endif // DELAUNAY_H
