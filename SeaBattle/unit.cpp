#include "unit.h"
#include <QDebug>
UNIT::UNIT(QObject *parent) : QObject(parent)
{
   //create key[10][10] from file
}

void UNIT::receiveFromQml()
{
    //count++;
    //emit sendToQml(count);
}
void UNIT::mouseClickEvent(QMouseEvent* e){
    qDebug()<<"!";
}
