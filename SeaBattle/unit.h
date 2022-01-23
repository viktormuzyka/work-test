#ifndef UNIT_H
#define UNIT_H

#include <QObject>
#include <QMouseEvent>
class UNIT : public QObject
{
    Q_OBJECT
public:
    explicit UNIT(QObject *parent = 0);

signals:
    void ToQml(char symb);

public slots:
    void cppSlot(int x, int y);

public:
    char key[10][10]; // '0' - sea, '1' - ship, '2' - dead, '3' - miss
    void start();
};

#endif