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

    void sendToQml(int count);

protected slots:

    void mouseClickEvent(QMouseEvent* e);

private:
    char key[10][10]; // '0' - sea, '1' - ship, '2' - dead, '3' - miss
};

#endif
