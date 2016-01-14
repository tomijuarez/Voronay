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
    for ( int i = 0; i < imax; i++ ) {
        qDebug() << "Resta: " << polygon.at(i) << " - " << polygon.at(i+1);
        result += (polygon.at(i).first * polygon.at(i+1).second) - (polygon.at(i+1).first * polygon.at(i).second);
    }
    qDebug() << "Resta: " << polygon.at(imax) << " - " << polygon.at(0);

    result += (polygon.at(imax).first * polygon.at(0).second) - (polygon.at(0).first * polygon.at(imax).second);

    double div = 2;
    qDebug() << "@@@@@@@";
    qDebug() << result/div;
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

    qDebug() << "********";
    qDebug() << "(" << result_x << "," << result_y << ")";

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

    double div = 2;

    double mid_x = inicio.first + ( (fin.first - inicio.first) / div );
    double mid_y = inicio.second + ( (fin.second - inicio.second) / div );
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

QList<QPair<double,double> > VoronoiCells::centroides(QList<QPair<double,double> > pointes, QList<Arista> edgees) {

    QList<Arista> edges;
    QList<QPair<double,double> > points;

    QPair<double,double> p1(10,200);
    QPair<double,double> p2(30,50);

    QPair<double,double> p3(10,200);
    QPair<double,double> p4(100,140);

    QPair<double,double> p5(10,200);
    QPair<double,double> p6(200,180);

    QPair<double,double> p7(30,50);
    QPair<double,double> p8(100,140);

    QPair<double,double> p9(30,50);
    QPair<double,double> p10(150,75);

    QPair<double,double> p11(30,50);
    QPair<double,double> p12(200,10);

    QPair<double,double> p13(100,140);
    QPair<double,double> p14(150,75);

    QPair<double,double> p15(100,140);
    QPair<double,double> p16(200,180);

    QPair<double,double> p17(150,75);
    QPair<double,double> p18(200,10);

    QPair<double,double> p19(150,75);
    QPair<double,double> p20(200,180);

    QPair<double,double> p21(150,75);
    QPair<double,double> p22(220,80);

    QPair<double,double> p23(200,10);
    QPair<double,double> p24(220,80);

    QPair<double,double> p25(200,10);
    QPair<double,double> p26(350,100);

    QPair<double,double> p27(200,180);
    QPair<double,double> p28(220,80);

    QPair<double,double> p29(200,180);
    QPair<double,double> p30(350,100);

    QPair<double,double> p31(220,80);
    QPair<double,double> p32(350,100);

    QPair<double,double> p33(50,130);
    QPair<double,double> p34(100,95);
    QPair<double,double> p35(100,170);
    QPair<double,double> p36(130,45);
    QPair<double,double> p37(150,130);
    QPair<double,double> p38(190,55);
    QPair<double,double> p39(190,110);
    QPair<double,double> p40(240,60);
    QPair<double,double> p41(245,120);

    Arista a1;
    Arista a2;
    Arista a3;
    Arista a4;
    Arista a5;
    Arista a6;
    Arista a7;
    Arista a8;
    Arista a9;
    Arista a10;
    Arista a11;
    Arista a12;
    Arista a13;
    Arista a14;
    Arista a15;
    Arista a16;
    Arista a17;

    a1.setPuntos(p1,p2);
    a2.setPuntos(p2,p3);
    a3.setPuntos(p4,p5);
    a4.setPuntos(p6,p7);
    a5.setPuntos(p8,p9);
    a6.setPuntos(p10,p11);
    a7.setPuntos(p12,p13);
    a8.setPuntos(p14,p15);
    a9.setPuntos(p16,p17);
    a10.setPuntos(p18,p19);
    a11.setPuntos(p20,p21);
    a12.setPuntos(p22,p23);
    a13.setPuntos(p24,p25);
    a14.setPuntos(p26,p27);
    a15.setPuntos(p28,p29);
    a16.setPuntos(p30,p31);
    a17.setPuntos(p32,p33);

    edges.push_back(a1);
    edges.push_back(a2);
    edges.push_back(a3);
    edges.push_back(a4);
    edges.push_back(a5);
    edges.push_back(a6);
    edges.push_back(a7);
    edges.push_back(a8);
    edges.push_back(a9);
    edges.push_back(a10);
    edges.push_back(a11);
    edges.push_back(a12);
    edges.push_back(a13);
    edges.push_back(a14);
    edges.push_back(a15);
    edges.push_back(a16);
    edges.push_back(a17);

    points.push_back(p34);
    points.push_back(p35);
    points.push_back(p36);
    points.push_back(p37);
    points.push_back(p38);
    points.push_back(p39);
    points.push_back(p40);
    points.push_back(p41);

    QList<QPair<double,double> > centroids;
    QList<QPair<double,double> > convexHull;

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

        convexHull = this->convex_hull_for_polygon(this->polygonPoints(cell_edges));

        centroids.push_back(this->centroid_for_polygon(convexHull));
    }

    QPair<double,double> centroide;
    qDebug() << "CONVEX HULL:*************";
    foreach(centroide, convexHull) {
        qDebug() << centroide;
    }

    qDebug() << "CENTROIDES:*************";
    foreach(centroide, centroids) {
        qDebug() << centroide;
    }

    return centroids;
}


/**
CUANDO CORRO EL ALGORITMO EL RESULTADO DA:

CENTROIDES:*************
QPair(84.1379,87.5287)
QPair(154.731,106.723)
QPair(84.1379,87.5287)
QPair(154.731,106.723)
QPair(154.731,106.723)
QPair(154.731,106.723)
QPair(176.514,93.2263)
QPair(154.731,106.723)

PERO TIENE QUE DAR:
        [46.6666666667, 130.0],
        [93.3333333333, 88.3333333333],
        [103.333333333, 173.333333333],
        [126.666666667, 45.0],
        [150.0, 131.666666667],
        [190.0, 55.0],
        [190.0, 111.666666667],
        [256.666666667, 63.3333333333],
        [256.666666667, 120.0]
  */
