#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "canhandler.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // --- The Modern Way ---
    // "PoloOS" is your URI from CMake
    // "Main" is the name of your file (without .qml)
    engine.loadFromModule("PoloOS", "Main");

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}


int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    // Register the class so QML can see it
    qmlRegisterType<CanHandler>("Polo.CAN", 1, 0, "CanHandler");

    QQmlApplicationEngine engine;
    engine.loadFromModule("PoloOS", "Main");
    return app.exec();
}
