#include "touchpad.h"

TouchPad::TouchPad(QObject *parent)
    : QObject(parent),
      m_window(NULL),
      xMultiplier(1),
      yMultiplier(1),
      touchPadWidth(320),
      touchPadHeight(240),
      mapWidth(640),
      mapHeight(480)
{
    // Note:: Touchpad needs to be opened before map.  That's fine since ICS services normally comes up way before the nav service anyway.
    map = new org::hondson::demo::Map("org.hondson.demo.Map", "/Map", QDBusConnection::sessionBus(), this);
    QObject::connect(map, SIGNAL(windowSizeChanged(int, int)), this, SLOT(onMapSizeChanged(int,int)));
}

TouchPad::~TouchPad()
{
    qDebug() << "Touch Destructed";
}

void TouchPad::setWindow(QObject *window)
{
    m_window = window;
}

QObject* TouchPad::getWindow()
{
    return m_window;
}

void TouchPad::onMapSizeChanged(int width, int height)
{
    mapWidth = width;
    mapHeight = height;

    calculateMultipliers();
}

void TouchPad::onTouchPadSizeChanged(int width, int height)
{
    touchPadWidth = width;
    touchPadHeight = height;

    calculateMultipliers();
}

void TouchPad::calculateMultipliers()
{
    if (mapWidth >= touchPadWidth && mapHeight >= touchPadHeight)
    {
        xMultiplier =  float(mapWidth / touchPadWidth);
        yMultiplier =  float(mapHeight/ touchPadHeight);

        if(xMultiplier == 0 || yMultiplier == 0)
            qDebug() << "Multipler could not be calculated";
    }
    else
    {
        qDebug() << "Uh-oh, looks like your mousepad is wider/taller than your screen...why would anyone want that?";
    }
}

void TouchPad::onClicked()
{
    map->onClicked();
}

void TouchPad::onDoubleClicked()
{
    map->onDoubleClicked();
}

void TouchPad::pan(int dx, int dy)
{
    map->pan(qRound(xMultiplier*dx), qRound(yMultiplier*dy));
}

void TouchPad::onSwiped(QString dir, int dist)
{
    map->swipe(dir, dist);
}
