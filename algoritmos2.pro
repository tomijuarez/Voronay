TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    classes/datamanager.cpp \
    classes/circunscripta.cpp \
    classes/delaunay.cpp \
    classes/triangulo.cpp \
    classes/voronoi.cpp \
    classes/grafohistorico.cpp \
    classes/nodografo.cpp \
    classes/arista.cpp


RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    classes/datamanager.h \
    classes/circunscripta.h \
    classes/delaunay.h \
    classes/triangulo.h \
    classes/voronoi.h \
    classes/grafohistorico.h \
    classes/nodografo.h \
    classes/arista.h

