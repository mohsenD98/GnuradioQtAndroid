#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QObject>

#include "ViewModels/GFlow.h"
#include "ViewModels/AndroidPermissions.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    GFlow flow;

    engine.rootContext()->setContextProperty("flow", &flow);
    engine.rootContext()->setContextProperty("androidPermissions", &AndroidPermissions::getInstance());

    engine.load("qrc:/main.qml");

    return app.exec();
}
