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
    bool encontrarContienePunto(QPair<float,float> punto);
    ~GrafoHistorico();
    NodoGrafo * getPrimero();
    NodoGrafo * getSegundo();
    NodoGrafo * busquedaSelectiva(QPair<float,float> punto, NodoGrafo * nodo);
    void clear();
    QList<Triangulo*> listarHojas();

private:
    void encontrar(NodoGrafo * nodo, QPair<float,float> punto, bool &encontrado);
    void listar(NodoGrafo * nodo);
    void limpiar(NodoGrafo * nodo);
    QList<Triangulo*> listaHojas;
    QList<NodoGrafo*> procesados;
    NodoGrafo * raiz;
    NodoGrafo * primero;
    NodoGrafo * segundo;
    QPair<float,float> p1;
    QPair<float,float> p2;
    QPair<float,float> p3;
};

#endif // GRAFOHISTORICO_H
