#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QObject>

#include "ViewModels/GFlow.h"
#include "ViewModels/AndroidPermissions.h"

#define qDebug qout

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    GFlow flow;
    AndroidPermissions androidPermissions;

    engine.rootContext()->setContextProperty("flow", &flow);
    engine.rootContext()->setContextProperty("androidPermissions", &androidPermissions);

    engine.load("qrc:/main.qml");

    return app.exec();
}
