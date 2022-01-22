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

    for(int i=0; i<10; i++){
        for(int j=0;j<10;j++){
            view.setSource(QUrl::fromLocalFile("MyRect.qml"));
            //std::cout << "yeap!" << std::endl;
            /*QQuickItem *item = view.rootObject()->findChild<QQuickItem*>("myRect");
            if (item){
                item->setProperty("x", 10*i +1);
                item->setProperty("y", 10*j +1);
               //std::cout << "work!" << std::endl;
               //item->setProperty("width", 1000);
            }*/
            view.show();
        }
    }


    //w.show();
    return a.exec();
}
