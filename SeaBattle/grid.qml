import QtQuick 2.0
import QtQuick.Layouts 1.12
Grid {
    x: 0; y: 0; width: 300; height: 300
    //anchors.fill: parent
    columns: 10; rows: 10; spacing: 0

    Repeater {
        model: 100
        Rectangle { color: "blue"; width: 30; height: 30; border { width: 1; color: "black" }
            MouseArea {
                    id: area
                    anchors.fill: parent
                    Connections {
                        target: unit
                        /*sendToQml: {
                            parent.color = 'red  '
                            console.log("clicked ",  (parent.x + x)/30 ," ",  (parent.y + y)/30);
                       }*/}

                    /*onClicked: {

                        parent.color = 'red  '
                        console.log("clicked ",  (parent.x + x)/30 ," ",  (parent.y + y)/30);
                    }*/
            }
        }
    }
}
