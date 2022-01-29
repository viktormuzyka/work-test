import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.12
import QtQml 2.15

Window {
    signal send(int x, int y, int index)
    width: 500
    height: 500
    visible: true

    Grid {
        x: 0; y: 0; width: 500; height: 500
        columns: 10; rows: 10; spacing: 0

        Repeater {
           id: repeater
           model: 100
           Rectangle { color: "gray"; width: 50; height: 50; border { width: 1; color: "black" }
               property int number
               number: index //from 1 to 100
               Connections {
                   target: object
                   onCppSignal:{
                       if(number==index){
                            console.log("Shoot! ", index, DeadShip);
                           if(DeadShip===true){
                                color = "red" //nice shot
                           }else{
                               color = "blue" //miss
                           }
                       }
                   }
               }
               MouseArea {
                       anchors.fill: parent
                       onClicked: {
                           send((parent.x+mouseX)/50, (parent.y+mouseY)/50, parent.number)
                       }
               }
         }
    }
    }
}
