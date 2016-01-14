#include "voronoicells.h"
#include "arista.h"
#include <QList>
#include <QDebug>
#include <QStack>
#include <QMap>

VoronoiCells::VoronoiCells()
{

}

double VoronoiCells::area_for_polygon(QList<QPair<double,double> > polygon) {
    double result = 0;
    double imax = polygon.size() - 1;
    for ( int i = 0; i < imax; i++ )
        result += (polygon.at(i).first * polygon.at(i+1).second) - (polygon.at(i+1).first * polygon.at(i).second);

    result += (polygon.at(imax).first * polygon.at(0).second) - (polygon.at(0).first * polygon.at(imax).second);

    double div = 2;
    return result / div;
}

QPair<double,double> VoronoiCells::centroid_for_polygon(QList<QPair<double,double> > polygon) {
    double area = area_for_polygon(polygon);
    double imax = polygon.size() - 1;

    double result_x = 0;
    double result_y = 0;

    for ( int i = 0; i < imax; i++ ) {
        result_x += (polygon.at(i).first + polygon.at(i+1).first) * ((polygon.at(i).first * polygon.at(i+1).second) - (polygon.at(i+1).first * polygon.at(i).second));
        result_y += (polygon.at(i).second + polygon.at(i+1).second) * ((polygon.at(i).first * polygon.at(i+1).second) - (polygon.at(i+1).first * polygon.at(i).second));
    }

    result_x += (polygon.at(imax).first + polygon.at(0).first) * ((polygon.at(imax).first * polygon.at(0).second) - (polygon.at(0).first * polygon.at(imax).second));
    result_y += (polygon.at(imax).second + polygon.at(0).second) * ((polygon.at(imax).first * polygon.at(0).second) - (polygon.at(0).first * polygon.at(imax).second));

    result_x = result_x / (area * 6.0);
    result_y = result_y / (area * 6.0);

    return QPair<double,double>(result_x, result_y);

}

int VoronoiCells::bottommost_index_for_polygon(QList<QPair<double,double> > polygon) {
    int bottommost_index = 0;
    for ( int i = 0; i < polygon.size(); i++ ) {
        if ( polygon.at(i).second < polygon.at(bottommost_index).second) {
            bottommost_index = i;
        }
    }

    return bottommost_index;
}

double VoronoiCells::angle_for_vector(QPair<double,double> start_point, QPair<double,double> end_point) {
    double y = end_point.second - start_point.second;
    double x = end_point.first - start_point.first;

    double angle;

    if (x == 0) {
        if (y > 0)
            angle = 90;
        else
            angle = 270;
    }
    else if (y == 0) {
        if (x > 0)
            angle = 0;
        else
            angle = 180;
    }

    else {
        double arc = qAtan(y/x);
        angle = qRadiansToDegrees(arc);
        if (x < 0)
            angle += 180;
        else if (y < 0)
            angle += 360;
    }

    return angle;
}

QList<QPair<double,double> > VoronoiCells::convex_hull_for_polygon(QList<QPair<double,double> > polygon) {
    int starting_point_index = this->bottommost_index_for_polygon(polygon);
    QList<QPair<double,double> > convex_hull;
    convex_hull.push_back(polygon.at(starting_point_index));
    int polygon_length = polygon.size();

    int hull_index_candidate = 0; //ARBITRARIO.
    int previous_hull_index_candidate = starting_point_index;
    double previous_angle = 0;
    while (true) {
        double smallest_angle = 360;

        for ( int j = 0; j < polygon_length; j++ ) {
            if (previous_hull_index_candidate == j)
                continue;
            int current_angle = angle_for_vector(polygon.at(previous_hull_index_candidate), polygon.at(j));

            if ( current_angle < smallest_angle && current_angle > previous_angle) {
                hull_index_candidate = j;
                smallest_angle = current_angle;
            }
        }

        if ( hull_index_candidate == starting_point_index ) { //ENVOLVIMOS LOS PUNTOS.
            break;
        }
        else {
            convex_hull.push_back(polygon.at(hull_index_candidate));
            previous_angle = smallest_angle;
            previous_hull_index_candidate = hull_index_candidate;
        }
    }

    return convex_hull;
}


QPair<double,double> VoronoiCells::midPoint(Arista arista) {
    QPair<double,double> inicio = arista.getInicio();
    QPair<double,double> fin = arista.getFin();

    double mid_x = inicio.first + ( (fin.first - inicio.first) / 2.0 );
    double mid_y = inicio.second + ( (fin.second - inicio.second) / 2.0 );
    return QPair<double,double>(mid_x, mid_y);
}

/**
 * http://www.bryceboe.com/2006/10/23/line-segment-intersection-algorithm/
 */

bool VoronoiCells::counterClockWise(QPair<double,double> A, QPair<double,double> B, QPair<double,double> C) {
    return ((C.second + A.second)*(B.first - A.first)) > ((B.second - A.second)*(C.first - A.first));
}

/**
 * http://www.bryceboe.com/2006/10/23/line-segment-intersection-algorithm/
 */

bool VoronoiCells::intersects(Arista arista1, Arista arista2) {
    QPair<double,double> A = arista1.getInicio();
    QPair<double,double> B = arista1.getFin();
    QPair<double,double> C = arista2.getInicio();
    QPair<double,double> D = arista2.getFin();

    return ((this->counterClockWise(A,C,D) != this->counterClockWise(B,C,D)) &&
            (this->counterClockWise(A,B,C) != this->counterClockWise(A,B,D))
            );
}

QList<QPair<double,double>> VoronoiCells::polygonPoints(QList<Arista> edges) {
        QSet<QPair<double,double> > point_set;

        Arista arista;
        for ( int i = 0; i < edges.size(); i++ ) {
            arista = edges.at(i);
            point_set.insert(arista.getInicio());
            point_set.insert(arista.getFin());
        }

        QList<QPair<double,double> > puntos;
        QPair<double,double> punto;
        foreach (punto, point_set)
            puntos.push_back(punto);

        return puntos;
}

QList<QPair<double,double> > VoronoiCells::centroides(QList<QPair<double,double> > points, QList<Arista> edges) {
    QList<QPair<double,double> > centroids;

    for(int i = 0; i < points.size(); i++) {
        QList<Arista> cell_edges;
        for(int j = 0; j < edges.size(); j++) {
            bool is_cell_edge = true;
            Arista vector;
            vector.setPuntos(points.at(i),this->midPoint(edges.at(j)));
            for ( int k = 0; k < edges.size(); k++) {
                if ( k != j && this->intersects(edges.at(k),vector)){
                    is_cell_edge = false;
                    break;
                }
            }

            if (is_cell_edge) {
                cell_edges.push_back(edges[j]);
            }
        }

        QList<QPair<double, double> > convexHull = this->convex_hull_for_polygon(this->polygonPoints(cell_edges));

        centroids.push_back(this->centroid_for_polygon(convexHull));
    }

    QPair<double,double> centroide;
    qDebug() << "CENTROIDES:*************";
    foreach(centroide, centroids) {
        qDebug() << centroide;
    }

    return centroids;
}

