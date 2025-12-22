#include <QGuiApplication>
#include <QQmlApplicationEngine>

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
