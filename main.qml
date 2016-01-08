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
        }
    }

    /**
     * Bloque contenedor del elemento Canvas.
     */

    Rectangle {
        id: rectangle1
        width: canvasWrapperWidthSize
        height: canvasWrapperHeightSize
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
                                controller.initIncrementalAlgorithm();
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
                                controller.initIncrementalAlgorithm();
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
            width: canvasWrapperWidthSize
            height: canvasHeight
            anchors.left: parent.left
            anchors.top: parent.top
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

            MouseArea {
                anchors.fill: parent;
                onClicked: {
                    Main.Drawer.repaint();
                    var x = mouseX, y = mouseY;
                    Main.Drawer.drawPoint(x-1,y-1);
                    controller.addPoint(x-1,y-1);
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
                            controller.initIncrementalAlgorithm();
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
                            controller.initIncrementalAlgorithm();
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
                            controller.initIncrementalAlgorithm();
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
                            controller.initIncrementalAlgorithm();
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
            Main.Drawer.drawPoint(x,y);
        }

        onDrawTriangle: {
            Main.Drawer.repaint();
            Main.Drawer.drawTriangle(x1,y1,x2,y2,x3,y3);
        }

        onDrawLine: {
            Main.Drawer.repaint();
            Main.Drawer.drawLine(x1,y1,x2,y2);
        }

        onDrawCircle: {
            Main.Drawer.repaint();
            Main.Drawer.drawCircle(x,y,radius);
        }
    }
}
