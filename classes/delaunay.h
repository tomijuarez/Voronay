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
    Delaunay(QList<QPair<float, float> > puntos, Triangulo *trianguloExterior);
    ~Delaunay();
    QList<Triangulo*> triangular();
    void resetear();
    QList<QPair<float, float> > getPuntos() const;
    void setPuntos(const QList<QPair<float, float> > &value);

    Triangulo *getTrianguloExterior() const;
    void setTrianguloExterior(Triangulo *value);

private:
    void insertarVertice(QPair<float, float> punto);
    void generarTriangulos(NodoGrafo * nodo, QPair<float, float> vertice );
    bool esLegal(QPair<float, float> punto1, QPair<float, float> punto2) const;
    void dividirTriangulos( NodoGrafo * nodo1, NodoGrafo * nodo2, QPair<float, float> vertice);
    float determinante(QPair<float, float> punto1, QPair<float, float> punto2,QPair<float, float> punto3);
    void legalizarLado(QPair<float, float> puntoNuevo, QPair<float, float> vertice1, QPair<float, float> vertice2, NodoGrafo * nodo);

    /**
     * Estructuras.
     */
    GrafoHistorico * grafoHistorico;
    QList<QPair<float,float> > puntos;
    QList<QPair<float, float> > puntosInsertados;
    Triangulo * trianguloExterior;

    bool calculada;
};

#endif // DELAUNAY_H
