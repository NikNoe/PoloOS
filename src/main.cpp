#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include "canhandler.h"
#include "CanReader.h"

int main(int argc, char *argv[])
{
    // FORCE LE STYLE ICI
    QQuickStyle::setStyle("Material");
    QGuiApplication app(argc, argv);

    // --- 1. CREATE THE SHARED INSTANCE ---
    // This is the SINGLE "Brain" of the car.
    CanHandler *canHandler = new CanHandler(&app);
    CanReader  *canReader  = new CanReader(canHandler, &app);
    canReader->connectToBus("can0");

    QQmlApplicationEngine engine;

    // --- 2. SHARE THE INSTANCE ---
    // We name it "carCan" so it matches your BodyPage code
    engine.rootContext()->setContextProperty("carCan", canHandler);
    // Also keeping "canHandler" alias just in case you used it elsewhere
    engine.rootContext()->setContextProperty("canHandler", canHandler);

    // --- 3. LOAD QML ---
    // loadFromModule fonctionne sur Qt 6.4, 6.5, 6.10+ sur toutes les plateformes
    // (Pi, ThinkPad, Mac) sans se soucier du préfixe qrc:/PoloOS/ vs qrc:/qt/qml/PoloOS/
    engine.loadFromModule("PoloOS", "Main");

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
