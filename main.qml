import QtQuick 2.3
import QtQuick.Window 2.2


import "./resources/js/main.js" as Main;

Window {
    /**
     * Definición de longitudes [píxeles].
     */

    property int mainWindowWidth: 1000
    property int mainWindowHeight: 600
    property int canvasWrapperWidthSize: 800
    property int leftMenuWidth: 200

    /**
     * Definición de colores [flat].
     */
    property string flatYellow   : "#F0D374"
    property string flatPurple   : "#906094"
    property string flatPink     : "#E082A5"
    property string flatLightBlue: "#46C8C8"
    property string flatOrange   : "#EE8677"
    property string flatBlue     : "#0287D0"


    visible: true

    width: mainWindowWidth
    height: mainWindowHeight

    /**
     * Menú lateral izquierdo.
     */

    Rectangle {
        width: leftMenuWidth
        height: parent.height

        anchors.left: parent.left

        Rectangle {
            width: parent.width
            height: 150
            anchors.top: parent.top

            Rectangle {
                width: 200
                height: 80
                color: "black"
                anchors {
                    top: parent.top
                }
            }

            Rectangle {
                width: 180
                height: 40
                color: flatBlue
                anchors {
                    top: parent.top
                    left: parent.left
                    topMargin: 100
                    leftMargin: 10
                }

                radius: 2


                Text {
                    anchors {
                        horizontalCenter: parent.horizontalCenter
                        centerIn: parent
                    }

                    font.pointSize: 13
                    text: "Algoritmo incremental"
                    color: "white"
                }

                MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        console.log("ola k tal?");
                        controller.addPoint(100,100);
                        controller.addPoint(200,100);
                        controller.addPoint(300,300);
                        controller.addPoint(89,250);
                        controller.addPoint(350,300);
                        controller.addPoint(200,400);
                        controller.initIncrementalAlgorithm();
                    }
                }

            }


            Rectangle {
                width: 180
                height: 40
                color: flatBlue
                anchors {
                    top: parent.top
                    left: parent.left
                    topMargin: 150
                    leftMargin: 10
                }

                radius: 2


                Text {
                    anchors {
                        horizontalCenter: parent.horizontalCenter
                        centerIn: parent
                    }

                    font.pointSize: 13
                    text: "Algoritmo de Fortune"
                    color: "white"
                }

                MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        console.log("ola k tal?");
                        controller.initFortunesAlgorithm();
                    }
                }

            }
        }
    }

    /**
     * Bloque contenedor del elemento Canvas.
     */

    Rectangle {
        width: canvasWrapperWidthSize
        height: parent.height

        anchors.right: parent.right

        border.color: "#CCC"

        Canvas {
            width: parent.width
            height: parent.height
            onPaint: {
                Main.Drawer.setCanvas(this);
            }
        }
    }

    /**
     * Handling de eventos.
     */

    Connections {
        target: controller

        /**
         * Propiedades.
         */

        /**
         * Eventos.
         */

        onDrawTriangle: {
            Main.Drawer.repaint();
            Main.Drawer.drawTriangle(x1,y1,x2,y2,x3,y3);
        }
    }
}

