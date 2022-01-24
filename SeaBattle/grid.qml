import QtQuick 2.0
import QtQuick.Layouts 1.12
Grid {
    signal send(int x, int y)
    signal receiveRed()
    signal receiveGray()
    onReceiveRed: {
        console.log("hello from QML");
        setProperty("color", 'red')
        console.log("Good Shoot!");
    }
    onReceiveGray: {
        console.log("hello from QML");
        setProperty("color", 'gray')
        console.log("Miss!")
    }

    x: 0; y: 0; width: 300; height: 300
    columns: 10; rows: 10; spacing: 0

    Repeater {
        model: 100
        Rectangle { color: "blue"; width: 30; height: 30; border { width: 1; color: "black" }
            MouseArea {
                    id: area
                    anchors.fill: parent
                    onClicked: send((parent.x+mouseX)/30, (parent.y+mouseY)/30)
            }
        }
    }
}
