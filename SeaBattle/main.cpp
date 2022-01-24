#include "mainwindow.h"
#include <QtQml>
#include <iostream>
#include <QApplication>
#include <QWidget>
#include <QtQuick/QQuickView>
#include <QtQuick/QQuickItem>
#include <QSize>
#include <QObject>
#include <QString>
#include "unit.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QQuickView view;
    UNIT *unit = new UNIT;
    //QString line;
    //build field
    unit->start();
    /*
     * Print field with ship
     */
    unit->print();
    /*
     * QML Field
     */
        view.setResizeMode(QQuickView::SizeViewToRootObject);
        view.setSource(QUrl::fromLocalFile("grid.qml"));
        QObject* obj = unit;
        QObject* root=view.rootObject();
        view.rootContext()->setContextProperty("UNIT", unit);
        QObject::connect(root, SIGNAL(send(int, int)), obj, SLOT(cppSlot(int, int)));
        /*QObject::connect(root, SIGNAL(ToQmlRed()), obj, SLOT(receiveRed()));
        QObject::connect(root, SIGNAL(ToQmlGray()), obj, SLOT(receiveGray()));*/
        /*QObject::connect(obj, SIGNAL(ToQmlRed()), root, SLOT(receiveRed()));
        QObject::connect(obj, SIGNAL(ToQmlGray()), root, SLOT(receiveGray()));*/

        /*QObject *object = view.rootObject();
        object->setProperty("color", "yellow");
        QQmlProperty(object, "color").write("yellow");*/
        view.show();
   // delete unit;
    return a.exec();
}
