#ifndef ARISTA_H
#define ARISTA_H

#include <QPair>
#include <QDebug>
#include <QLineF>
#include <QPointF>

class Arista
{
public:
    Arista();
    void setPuntos(QPair<double,double> inicio, QPair<double,double> fin);
    QPair<double,double> getInicio();
    QPair<double,double> getFin();

    void limitarAInterseccion(Arista limite, Arista & nueva) {

        nueva.setPuntos(this->getInicio(),this->getFin());
        QPair<double,double> interseccion;

        if (this->intersecta(limite)) {
            interseccion = this->getPuntoInterseccion(limite);

            if (fabs(this->getInicio().first) >= 500 || fabs(this->getInicio().second) >= 500) {
                nueva.setPuntos(interseccion,this->getFin());
            }
            else
                if(fabs(this->getFin().first) >= 500 || fabs(this->getFin().second) >= 500) {
                    nueva.setPuntos(this->getInicio(),interseccion);
                }
        }

    }

    QPair<double,double> getPuntoInterseccion(Arista otra) {
        QLineF actual(this->getInicio().first,this->getInicio().second,this->getFin().first,this->getFin().second);
        QLineF secundaria(otra.getInicio().first,otra.getInicio().second,otra.getFin().first,otra.getFin().second);

        QPointF interseccion;
        actual.intersect(secundaria,&interseccion);

        return QPair<double,double>(interseccion.x(), interseccion.y());
    }

    bool intersecta(Arista otra) {
        QLineF actual(this->getInicio().first,this->getInicio().second,this->getFin().first,this->getFin().second);
        QLineF secundaria(otra.getInicio().first,otra.getInicio().second,otra.getFin().first,otra.getFin().second);

        QPointF interseccion;
        int interseca = actual.intersect(secundaria,&interseccion);

        return (interseca == QLineF::BoundedIntersection);
    }

private:
    QPair<double,double> inicio;
    QPair<double,double> fin;
};

#endif // ARISTA_H
