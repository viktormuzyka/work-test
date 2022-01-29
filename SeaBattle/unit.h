#ifndef UNIT_H
#define UNIT_H

#include <QObject>
#include <QQuickItem>

class unit: public QObject
{
    Q_OBJECT
public:
    QQuickItem* qField;
    unit();
    void start(); // get keys.. keys - blocks with ships/water
    void print();
    char keys[100]; // 0 - water, 1 - ship
public slots:
    void cppSlot(int x, int y, int index);
signals:
    void cppSignal(int index, bool DeadShip);
};

#endif // UNIT_H
