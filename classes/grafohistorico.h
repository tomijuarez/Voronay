#ifndef GRAFOHISTORICO_H
#define GRAFOHISTORICO_H

#include <QList>
#include <QPair>
#include "triangulo.h"
#include "nodografo.h"

class GrafoHistorico
{
public:
    GrafoHistorico(Triangulo * t);
    bool encontrarContienePunto(QPair<double,double> punto);
    ~GrafoHistorico();
    NodoGrafo * getPrimero();
    NodoGrafo * getSegundo();
    NodoGrafo * busquedaSelectiva(QPair<double,double> punto, NodoGrafo * nodo);
    void clear();

private:
    void encontrar(NodoGrafo * nodo, QPair<double,double> punto, bool &encontrado);
    void limpiar(NodoGrafo * nodo);
    QList<Triangulo*> listaHojas;
    QList<NodoGrafo*> procesados;
    NodoGrafo * raiz;
    NodoGrafo * primero;
    NodoGrafo * segundo;
    QPair<double,double> p1;
    QPair<double,double> p2;
    QPair<double,double> p3;
    bool flagYaPertenece = false;
};

#endif // GRAFOHISTORICO_H
