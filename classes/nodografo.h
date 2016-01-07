#ifndef NODOGRAFO_H
#define NODOGRAFO_H

#include "triangulo.h"
#include <QList>

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
    ~NodoGrafo();
private:
    Triangulo * triangulo;
    QList<NodoGrafo*> hijos;
    bool procesado; // al momento de listar las hojas nos sirve para no listarlo doble en caso de
                    //ser apuntado por mas de un nodo
};

#endif // NODOGRAFO_H
