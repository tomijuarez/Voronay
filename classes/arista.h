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

    void limitarAInterseccion(Arista limite) {
        double limit = 500;

        QPair<double,double> interseccion;

        if (this->intersecta(limite)) {
            interseccion = this->getPuntoInterseccion(limite);

            qDebug() << "LA LINEA " << this->getInicio() << " , " << this->getFin() << " SE INTERSECA CON LA LINEA " << limite.getInicio() << " , " << limite.getFin();

            qDebug() << "EN EL PUNTO " << interseccion;

            if (fabs(this->getInicio().first) >= limit || fabs(this->getInicio().second) >= limit) {
                qDebug() << this->getInicio().first << " , " << this->getInicio().second << " >= " << limit;
                this->inicio = interseccion;
            }
            else
                if(fabs(this->getFin().first) >= limit || fabs(this->getFin().second) >= limit) {
                    qDebug() << this->getFin().first << " , " << this->getFin().second << " >= " << limit;
                    this->fin = interseccion;
                }
        }

        qDebug() << "AHORA ES " << this->getInicio() << " / " << this->getFin();
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
