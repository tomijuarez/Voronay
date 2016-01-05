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
    QList<Triangulo*> listarHojas();

private:
    void encontrar(NodoGrafo * nodo, QPair<float,float> punto, bool &encontrado);
    void listar(NodoGrafo * nodo);
    QList<Triangulo*> listaHojas;
    NodoGrafo * raiz;
    NodoGrafo * primero;
    NodoGrafo * segundo;
};

#endif // GRAFOHISTORICO_H
