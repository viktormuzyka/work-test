#include "unit.h"
#include <QDebug>
#include <fstream>
UNIT::UNIT(QObject *parent) : QObject(parent)
{
   //create key[10][10] from file
}
void UNIT::start(){
    std::ifstream file("data.txt");
    for(int i=0; i<10; i++){
        for(int j=0;j<10; j++){
            file >> this->key[i][j];
        }
    }
}

void UNIT::mouseClickEvent(QMouseEvent* e){
    qDebug()<<"!";
}
