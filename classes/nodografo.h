#ifndef NODOGRAFO_H
#define NODOGRAFO_H

#include <QList>
#include <QDebug>
#include "triangulo.h"

class NodoGrafo
{
public:
    NodoGrafo(Triangulo * t);
    Triangulo * getTriangulo();
    QList<NodoGrafo*> getHijos();
    void agregarHijo(NodoGrafo * n);
    bool getProcesado() const;
    void setProcesado(bool value);
    void clear();
    void imprimir() {
        qDebug()<< "************************";
        this->triangulo->imprimir();
    }

    ~NodoGrafo();
private:
    Triangulo * triangulo;
    QList<NodoGrafo*> hijos;
    bool procesado; // al momento de listar las hojas nos sirve para no listarlo doble en caso de
                    //ser apuntado por mas de un nodo
};

#endif // NODOGRAFO_H
