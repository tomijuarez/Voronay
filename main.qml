import QtQuick 2.3
import QtQuick.Window 2.2


import "./resources/js/main.js" as Main;

Window {
    id: window1

    property bool sameScene: false

    /**
     * Definición de longitudes [píxeles].
     */

    property int mainWindowWidth: 1020
    property int mainWindowHeight: 600
    property int canvasWrapperWidthSize: 800
    property int canvasWrapperHeightSize : 600
    property int canvasHeight : 570
    property int leftMenuWidth: 220

    /**
     * Definición de colores [flat].
     */
    property string flatYellow   : "#F0D374"
    property string flatPurple   : "#906094"
    property string flatPink     : "#E082A5"
    property string flatLightBlue: "#46C8C8"
    property string flatBlue     : "#0287D0"
    property string flatGreen    : "#00B16A"


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
                width: 220
                height: 80
                color: "black"
                anchors {
                    top: parent.top
                }
            }

            Rectangle {
                width: 200
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

                    font.pointSize: 12
                    text: "Triangulación de Delaunay"
                    color: "white"
                }

                MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        controller.initIncrementalAlgorithm();
                    }
                }
            }

            Rectangle {
                width: 200
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

                    font.pointSize: 12
                    text: "Resetear"
                    color: "white"
                }

                MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        console.log("Reseteando");
                        controller.reset();
                    }
                }
            }

            Rectangle {
                width: 200
                height: 40
                color: "transparent"
                anchors {
                    top: parent.top
                    left: parent.left
                    topMargin: 200
                    leftMargin: 10
                }

                Row {
                    spacing: 25
                    Rectangle {
                        color: flatBlue;
                        width: 50;
                        height: 36
                        Text {
                            anchors {
                                horizontalCenter: parent.horizontalCenter
                                centerIn: parent
                            }

                            font.pointSize: 12
                            text: "T"
                            color: "white"
                        }

                          MouseArea {
                            anchors.fill: parent

                            onClicked: {
                                controller.changeDrawTriangles();
                                if(parent.color == "#0287d0"){
                                    parent.color = flatLightBlue;
                                }else{
                                    parent.color = flatBlue;
                                }
                                controller.refresh();
                            }
                         }
                       }
                    Rectangle {
                        color: flatBlue;
                        width: 50;
                        height: 36
                        Text {
                            anchors {
                                horizontalCenter: parent.horizontalCenter
                                centerIn: parent
                            }

                            font.pointSize: 12
                            text: "C"
                            color: "white"
                        }

                          MouseArea {
                            anchors.fill: parent

                            onClicked: {
                                controller.changeDrawCircles();
                                if(parent.color == "#0287d0"){
                                    parent.color = flatLightBlue;
                                }else{
                                    parent.color = flatBlue;
                                }
                                controller.refresh();
                            }
                         }
                       }
                    Rectangle {
                        color: flatBlue;
                        width: 50;
                        height: 36
                        Text {
                            anchors {
                                horizontalCenter: parent.horizontalCenter
                                centerIn: parent
                            }

                            font.pointSize: 12
                            text: "V"
                            color: "white"
                        }

                          MouseArea {
                            anchors.fill: parent

                            onClicked: {
                                controller.changeDrawVoronoi();
                                if(parent.color == "#0287d0"){
                                    parent.color = flatLightBlue;
                                }else{
                                    parent.color = flatBlue;
                                }
                                controller.refresh();
                            }
                         }
                       }
                }
            }
        }
    }

    /**
     * Bloque contenedor del elemento Canvas.
     */

    Rectangle {
        id: rectangle1
        width: parent.width - leftMenuWidth
        height: parent.height
        color: "#EEE"
        anchors.verticalCenter: parent.verticalCenter

        anchors.right: parent.right

        border.color: "#CCC"

        Rectangle {
            id: canvasControls
            height: 30
            width: parent.width - 2

            anchors {
                left: parent.left
                leftMargin: 2
            }

            Row {
                id: row1
                x: 0
                y: 1
                width: 200
                height: 28
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter

                Row {
                    id: zoomControls
                    width: 70
                    height: 28

                    Rectangle {
                        id: zoomInButton
                        x: 2
                        width: 30
                        height: 28
                        color: flatLightBlue
                        radius: 3

                        anchors {
                            left: parent.left
                            leftMargin: 3
                        }

                        Text {
                            anchors.centerIn: parent
                            font.pixelSize: 20
                            color: "white"
                            text: "+"
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                Main.Drawer.zoomIn();
                                controller.refresh();
                            }
                        }
                    }

                    Rectangle {
                        id: zoomOutButton
                        x: 36
                        width: 30
                        height: 28
                        color: flatLightBlue
                        radius: 3

                        Text {
                            anchors.centerIn: parent
                            font.pixelSize: 20
                            color: "white"
                            text: "–"
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                Main.Drawer.zoomOut();
                                controller.refresh();
                            }
                        }
                    }
                }
            }
        }
        Canvas {
            id: canvas1
            x: 0
            y: 30
            width: parent.width
            height: parent.height - 30
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.topMargin: 30


            /**
             * Render properties.
             */

            contextType: "2d";
            renderStrategy: Canvas.Threaded;
            renderTarget: Canvas.Image;
            antialiasing: true;
            smooth: true;

            onPaint: {
                Main.Drawer.setCanvas(this);
            }

            onCanvasSizeChanged: {
                controller.refresh()
            }

            MouseArea {
                anchors.fill: parent;
                onClicked: {
                    Main.Drawer.repaint();
                    var x = mouseX, y = mouseY;
                    Main.Drawer.drawPoint(x-1,y-1);
                    controller.addPoint(Main.Drawer.translateHorizontalClick(x-1),Main.Drawer.translateVerticalClick(y-1));
                }
            }

            Rectangle {
                height:90
                width:90
                anchors {
                    right: parent.right
                    top: parent.top
                    rightMargin: 10
                    topMargin: 10
                }

                color: "transparent"

                Rectangle {
                    height: 30
                    width: 30
                    radius: 3
                    border.color: "#CCC"
                    color: "white"
                    anchors {
                        top: parent.top
                        left: parent.left
                        leftMargin: 30
                    }
                    Text {
                        anchors.centerIn: parent
                        color: "#CCC"
                        font.pixelSize: 17
                        text: "▲"
                    }
                    MouseArea {
                        anchors.fill:parent
                        onClicked: {
                            Main.Drawer.down();
                            controller.refresh();
                        }
                    }
                }

                Rectangle {
                    height: 30
                    width: 30
                    radius: 3
                    border.color: "#CCC"
                    color: "white"
                    anchors {
                        top: parent.top
                        left: parent.left
                        topMargin: 30
                    }
                    Text {
                        anchors.centerIn: parent
                        color: "#CCC"
                        font.pixelSize: 17
                        text: "◄"
                    }
                    MouseArea {
                        anchors.fill:parent
                        onClicked: {
                            Main.Drawer.right();
                            controller.refresh();
                        }
                    }
                }

                Rectangle {
                    height: 30
                    width: 30
                    radius: 3
                    border.color: "#CCC"
                    color: "white"
                    anchors {
                        top: parent.top
                        right: parent.right
                        topMargin: 30
                    }
                    Text {
                        anchors.centerIn: parent
                        color: "#CCC"
                        font.pixelSize: 17
                        text: "►"
                    }
                    MouseArea {
                        anchors.fill:parent
                        onClicked: {
                            Main.Drawer.left();
                            controller.refresh();
                        }
                    }
                }

                Rectangle {
                    height: 30
                    width: 30
                    radius: 3
                    border.color: "#CCC"
                    color: "white"
                    anchors {
                        bottom: parent.bottom
                        left: parent.left
                        leftMargin: 30
                    }
                    Text {
                        anchors.centerIn: parent
                        color: "#CCC"
                        font.pixelSize: 17
                        text: "▼"
                    }
                    MouseArea {
                        anchors.fill:parent
                        onClicked: {
                            Main.Drawer.up();
                            controller.refresh();
                        }
                    }
                }
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

        onCleanScene: {
            Main.Drawer.repaint();
            Main.Drawer.clear();
        }

        onDrawPoint: {
            Main.Drawer.repaint();
            Main.Drawer.drawPoint(Main.Drawer.translateHorizontal(x),Main.Drawer.translateVertical(y));
        }

        onDrawTriangle: {
            Main.Drawer.repaint();
            Main.Drawer.drawTriangle(Main.Drawer.translateHorizontal(x1),Main.Drawer.translateVertical(y1),Main.Drawer.translateHorizontal(x2),Main.Drawer.translateVertical(y2),Main.Drawer.translateHorizontal(x3),Main.Drawer.translateVertical(y3));
        }

        onDrawLine: {
            Main.Drawer.repaint();
            Main.Drawer.drawLine(Main.Drawer.translateHorizontal(x1),Main.Drawer.translateVertical(y1),Main.Drawer.translateHorizontal(x2),Main.Drawer.translateVertical(y2));
        }

        onDrawCircle: {
            Main.Drawer.repaint();
            Main.Drawer.drawCircle(Main.Drawer.translateHorizontal(x),Main.Drawer.translateVertical(y),Main.Drawer.translateZoomNumberPoint(radius));
        }

        onDrawPaintedCircle: {
            Main.Drawer.repaint();
            Main.Drawer.drawPaintedCircle(Main.Drawer.translateHorizontal(x),Main.Drawer.translateVertical(y),Main.Drawer.translateZoomNumberPoint(radius));
        }
    }
}
