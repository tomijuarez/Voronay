#include <QQmlApplicationEngine>
#include <QDebug>
#include <QObject>
#include <QGuiApplication>
#include <QQuickItem>
#include <QQmlContext>
#include "classes/datamanager.h"

int main(int argc, char *argv[]) {

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    DataManager controller;
    QQmlContext* ctx = engine.rootContext();
    ctx->setContextProperty("controller", &controller);
    engine.load(QUrl(QStringLiteral("qrc:./main.qml")));
    return app.exec();
}
