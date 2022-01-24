#include "unit.h"
#include <QDebug>
#include <fstream>
#include <QString>
UNIT::UNIT(QObject *parent) : QObject(parent)
{
   //create key[10][10] from file
}
//maybe better do this in constructor..
void UNIT::start(){ // in ideal add check for correct location of all ship
    std::ifstream file("data.txt");
    for(int i=0; i<10; i++){
        for(int j=0;j<10; j++){
            file >> this->key[j][i];
        }
    }
    file.close();
}
void UNIT::print(){
    QString line;
    for(int i=0; i<10; i++){
        for(int j=0;j<10; j++){
           line = line +  this->key[i][j] + " ";
        }
        qDebug()<< line ;
        line="";
    }
}
void UNIT::cppSlot(int x, int y){
    qDebug()<<"Shoot: x="<<x<<" y= "<<y;
    if (this->key[x][y]=='0'){  // '0' - sea, '1' - ship, '2' - dead zone, '3' - miss
        key[x][y]='3';
        qDebug()<<"cpp: x="<<x<<" y= "<<y<<" miss";
        emit this->ToQmlRed();
    } else if (this->key[x][y]=='1') {
        key[x][y]='2';
        qDebug()<<"cpp: x="<<x<<" y= "<<y<<" shoot in"; //in ideal add state - dead ship
        emit this->ToQmlGray();
    } else {
        qDebug("You are already shoot in this area! Miss!");
    }
}
