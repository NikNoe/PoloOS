#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QUrl>
#include <QQmlContext>
#include <QQuickStyle>
#include "canhandler.h"

int main(int argc, char *argv[])
{
    // FORCE LE STYLE ICI
    QQuickStyle::setStyle("Material");

    QGuiApplication app(argc, argv);

    // --- 1. CREATE THE SHARED INSTANCE ---
    // This is the SINGLE "Brain" of the car.
    CanHandler *canHandler = new CanHandler(&app);

    QQmlApplicationEngine engine;

    // --- 2. SHARE THE INSTANCE ---
    // We name it "carCan" so it matches your BodyPage code
    engine.rootContext()->setContextProperty("carCan", canHandler);

    // Also keeping "canHandler" alias just in case you used it elsewhere
    engine.rootContext()->setContextProperty("canHandler", canHandler);

    #if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
        const QUrl url(QStringLiteral("qrc:/qt/qml/PoloOS/Main.qml"));
    #else
        const QUrl url(QStringLiteral("qrc:/PoloOS/Main.qml"));
    #endif

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                         if (!obj && url == objUrl)
                             QCoreApplication::exit(-1);
                     }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
