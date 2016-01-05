TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    classes/datamanager.cpp \
    classes/circunscripta.cpp \
    classes/delaunay.cpp \
    classes/grafohistorico.cpp \
    classes/linea.cpp \
    classes/nodografo.cpp \
    classes/triangulo.cpp \
    classes/voronoi.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    classes/datamanager.h \
    classes/circunscripta.h \
    classes/delaunay.h \
    classes/grafohistorico.h \
    classes/linea.h \
    classes/nodografo.h \
    classes/triangulo.h \
    classes/voronoi.h

