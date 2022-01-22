#include "mainwindow.h"
#include <QtQml>
#include <iostream>
#include <QApplication>
#include <QWidget>
#include <QtQuick/QQuickView>
#include <QtQuick/QQuickItem>
#include <QSize>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QQuickView view;
    view.setResizeMode(QQuickView::SizeViewToRootObject);

            view.setSource(QUrl::fromLocalFile("MyRect.qml"));

            /*QQuickItem *item = view.rootObject()->findChild<QQuickItem*>("myRect");
            if (item){            
               //item->setProperty("width", 1000);
            }*/

            view.show();
    //w.show();
    return a.exec();
}
