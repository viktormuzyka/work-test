#include "unit.h"
#include <fstream>
unit::unit()
{
    start();
}
void unit::start(){ // in ideal add check for correct location of all ship
    std::ifstream file("data.txt");
    for(int i=0; i<100; i++){
        file >> this->keys[i];
    }
    file.close();
}
void unit::print(){
    QString line;
    for(int i=0; i<90; i+=10){
        for(int j=i;j<i+10; j++){
           line = line +  this->keys[j] + " ";
        }
        qDebug()<< line ;
        line="";
    }
}
void unit::cppSlot(int x, int y, int index){
    qDebug()<<"Area: x="<<x<<" y= "<<y<<" index: "<<index;
    bool value = false;
    if (keys[index]=='1'){
        value = true;
    }
    emit cppSignal(index, value);
}
