#include <QQmlApplicationEngine>
#include <QDebug>
#include <QObject>
#include <QGuiApplication>
#include <QQuickView>
#include "classes/datamanager.h"
#include <QQuickItem>
#include <QQmlContext>

int main(int argc, char *argv[]) {

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    DataManager controller;
    QQmlContext* ctx = engine.rootContext();
    ctx->setContextProperty("controller", &controller);
    engine.load(QUrl(QStringLiteral("qrc:./main.qml")));
    return app.exec();
}
