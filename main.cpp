#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QUrl>
#include "canhandler.h"
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // 1. Register the C++ CAN logic for QML
    qmlRegisterType<CanHandler>("Polo.CAN", 1, 0, "CanHandler");

    QQmlApplicationEngine engine;

    // 2. Use the standard QUrl constructor (No special suffixes like _s or _u)
    const QUrl url(QStringLiteral("qrc:/qt/qml/PoloOS/Main.qml"));

    // 3. Connect error handling to ensure we know if the QML fails to load
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                         if (!obj && url == objUrl)
                             QCoreApplication::exit(-1);
                     }, Qt::QueuedConnection);

    CanHandler *canHandler = new CanHandler(&app);
    engine.rootContext()->setContextProperty("canHandler", canHandler);

    engine.load(url);

    return app.exec();
}


