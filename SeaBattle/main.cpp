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
    UNIT unit;
    QString line;
    //build field
    unit.start();
    /*
     * Print field with ship
     */
    for(int i=0; i<10; i++){
        for(int j=0;j<10; j++){
           line = line +  unit.key[i][j] + " ";
        }
        qDebug()<< line ;
        line="";
    }
    /*
     * QML Field
     */
        view.setResizeMode(QQuickView::SizeViewToRootObject);
        view.setSource(QUrl::fromLocalFile("grid.qml"));
        /*QObject *object = view.rootObject();
        object->setProperty("color", "yellow");
        QQmlProperty(object, "color").write("yellow");*/
        view.show();

    return a.exec();
}
