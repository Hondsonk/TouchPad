#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "../Map/map_interface.h"
#include "touchpad.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    TouchPad touchPad(&engine);
    touchPad.setWindow(engine.rootObjects().at(0));

    QObject::connect(touchPad.getWindow(), SIGNAL(clicked()), &touchPad, SLOT(onClicked()));
    QObject::connect(touchPad.getWindow(), SIGNAL(doubleClicked()), &touchPad, SLOT(onDoubleClicked()));
    QObject::connect(touchPad.getWindow(), SIGNAL(pan(int, int)), &touchPad, SLOT(pan(int,int)));
    QObject::connect(touchPad.getWindow(), SIGNAL(windowSizeChanged(int, int)), &touchPad, SLOT(onTouchPadSizeChanged(int,int)));
    QObject::connect(touchPad.getWindow(), SIGNAL(swipe(QString, int)), &touchPad, SLOT(onSwiped(QString, int)));
    return app.exec();
}
