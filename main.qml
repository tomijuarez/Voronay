import QtQuick 2.3
import QtQuick.Window 2.2


import "./resources/js/main.js" as Main;

Window {
    id: window1

    property bool sameScene: false

    /**
     * Definición de longitudes [píxeles].
     */

    property int mainWindowWidth: 1000
    property int mainWindowHeight: 600
    property int canvasWrapperWidthSize: 800
    property int canvasWrapperHeightSize : 600
    property int canvasHeight : 570
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
//                        controller.addPoint(202,244);
//                        controller.addPoint(285,144);
//                        controller.addPoint(420,218);
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

            Rectangle {
                width: 180
                height: 40
                color: flatBlue
                anchors {
                    top: parent.top
                    left: parent.left
                    topMargin: 200
                    leftMargin: 10
                }

                radius: 2


                Text {
                    anchors {
                        horizontalCenter: parent.horizontalCenter
                        centerIn: parent
                    }

                    font.pointSize: 13
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
        color: "#cccccc"
        anchors.verticalCenter: parent.verticalCenter

        anchors.right: parent.right

        border.color: "#CCC"

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
                    width: 65
                    height: 28

                    Rectangle {
                        id: zoomInButton
                        x: 2
                        width: 30
                        height: 28
                        color: "#de2121"
                        clip: false

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                Main.Drawer.zoomIn();
                                controller.initIncrementalAlgorithm();
                            }
                        }
                    }

                    Rectangle {
                        id: rectangle4
                        x: 32
                        width: 1
                        height: 28
                        color: "#0056ad"
                    }

                    Rectangle {
                        id: zoomOutButton
                        x: 33
                        width: 30
                        height: 28
                        color: "#c55cfa"

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                Main.Drawer.zoomOut();
                                controller.initIncrementalAlgorithm();
                            }
                        }
                    }
                }

                Rectangle {
                    width: 200
                    height: 28
                    anchors {
                        left: parent.left
                        top: parent.top
                        leftMargin: 70
                    }
                    radius: 3
                    color: flatBlue
                    Text {
                        anchors.centerIn: parent
                        text: "Agregar nuevos puntos"
                        font.pixelSize: 17
                        color: "white"
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            controller.reset();
                            Main.Drawer.clear();
                            sameScene = false;
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
            console.log("TRIANGULITOOO-");
            Main.Drawer.repaint();
            Main.Drawer.drawTriangle(x1,y1,x2,y2,x3,y3);
        }
    }
}
