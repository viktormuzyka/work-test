#ifndef UNIT_H
#define UNIT_H

#include <QObject>
#include <QMouseEvent>
#include <QtQuick/QQuickView>
class UNIT : public QObject
{
    Q_OBJECT
public:
    explicit UNIT(QObject *parent = 0);
signals:
    void toQmlRed();
    void toQmlBlue();
public slots:
    void cppSlot(int x, int y);

public:
   // QQuickView *view; //maybe better to work with slots in qml
    char key[10][10]; // '0' - sea, '1' - ship, '2' - dead zone, '3' - miss
    void start();
    void print();
};

#endif
