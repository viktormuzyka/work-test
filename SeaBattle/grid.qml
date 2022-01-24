import QtQuick 2.0
import QtQuick.Layouts 1.12
Grid {
    signal send(int x, int y)
    Connections {
        target: UNIT
        onToQmlRed: {
            //console.log("hello from QML1");
            //parent.color="red"
            console.log("Good Shoot!");

        }

    }

    Connections {
        target: UNIT
        onToQmlBlue: {
            //console.log("hello from QML2");
            //setProperty("color", 'blue')
            console.log("Miss!")
        }
    }
    x: 0; y: 0; width: 300; height: 300
    columns: 10; rows: 10; spacing: 0

    Repeater {
        id: repeater
        model: 100

        Rectangle { objectName: "rect"; color: "gray"; width: 30; height: 30; border { width: 1; color: "black" }
            MouseArea {
                    id: area
                    anchors.fill: parent
                    onClicked: {
                        parent.objectName = "current"
                        parent.color = "red" //when you shoot rectangle turns red, one color - bad ...
                        send((parent.x+mouseX)/30, (parent.y+mouseY)/30 )
                       }
                 }
          }
    }
}
