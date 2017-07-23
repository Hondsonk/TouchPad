#ifndef TOUCHPAD_H
#define TOUCHPAD_H

#include <QObject>
#include <QWindow>
#include <QDebug>
#include <QMetaEnum>
#include "../Map/map_interface.h"

class TouchPad : public QObject
{
    Q_OBJECT
    Q_ENUMS(Directions)

public:
    explicit TouchPad(QObject *parent = nullptr);
    ~TouchPad();
    // Note: these enums need to match up with the readonly properties in main.qml
    enum Directions { up, down, left, right };

    void setWindow(QObject*);
    QObject* getWindow();

private slots:
    void onClicked();
    void onDoubleClicked();
    void pan(int, int);
    void onMapSizeChanged(int, int);
    void onTouchPadSizeChanged(int, int);
    void onSwiped(QString, int);

private:
    org::hondson::demo::Map *map;
    void calculateMultipliers();
    QObject *m_window;
    float xMultiplier;
    float yMultiplier;
    int touchPadWidth;
    int touchPadHeight;
    int mapWidth;
    int mapHeight;
};

#endif // TOUCHPAD_H
