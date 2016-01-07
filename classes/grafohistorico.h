#ifndef GRAFOHISTORICO_H
#define GRAFOHISTORICO_H

#include "triangulo.h"
#include "nodografo.h"
#include <QList>
#include <QPair>

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
    QList<Triangulo*> listarHojas();

private:
    void encontrar(NodoGrafo * nodo, QPair<double,double> punto, bool &encontrado);
    void listar(NodoGrafo * nodo);
    void limpiar(NodoGrafo * nodo);
    QList<Triangulo*> listaHojas;
    QList<NodoGrafo*> procesados;
    NodoGrafo * raiz;
    NodoGrafo * primero;
    NodoGrafo * segundo;
    QPair<double,double> p1;
    QPair<double,double> p2;
    QPair<double,double> p3;
};

#endif // GRAFOHISTORICO_H
