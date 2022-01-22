import QtQuick 2.0
import QtQuick.Layouts 1.12
Grid {
    x: 15; y: 15; width: 400; height: 400

    columns: 10; rows: 10; spacing: 1

    Repeater {
        model: 100
        Rectangle { color: "blue"; width: 30; height: 30; border { width: 1; color: "black" }}
    }


}
