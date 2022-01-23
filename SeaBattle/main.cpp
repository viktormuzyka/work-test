#include "mainwindow.h"
#include <QtQml>
#include <iostream>
#include <QApplication>
#include <QWidget>
#include <QtQuick/QQuickView>
#include <QtQuick/QQuickItem>
#include <QSize>
#include <QObject>
#include "unit.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QQuickView view;
   // UNIT unit;
    view.setResizeMode(QQuickView::SizeViewToRootObject);

    view.setSource(QUrl::fromLocalFile("grid.qml"));

    /*QObject *object = view.rootObject();
    object->setProperty("color", "yellow");
    QQmlProperty(object, "color").write("yellow");*/

    view.show();

    return a.exec();
}
