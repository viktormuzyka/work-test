import QtQuick 2
import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.15
import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.5
import Qt.labs.folderlistmodel 2.2
import Qt.labs.folderlistmodel 2.1
import Qt.labs.platform 1.0

Window {
    id:main_window
    visible: true
    width: 640
    height: 480
    title: qsTr("photoViewer")
    Rectangle {
        width: parent.width
        height: 50
        color: "gray"
        visible: listView.contentY >= -50
        z: 10
        RoundButton {
            id: list
            width: 40
            height: 40
            anchors.verticalCenter: parent.verticalCenter
            x: 5
            radius: 4
            text: "list"
            onClicked: {
                pathView.visible = false
                rowView.visible = true
                listView.visible = true
                gridView.visible = false
            }

        }
        RoundButton {
            id: grid
            width: 40
            height: 40
            anchors.verticalCenter: parent.verticalCenter
            x: 50
            radius: 4
            text: "table"
            onClicked: {
                pathView.visible = false
                rowView.visible = true
                gridView.visible = true
                listView.visible = false
            }
        }
        RoundButton {
            id: slider
            width: 80
            height: 40
            anchors.verticalCenter: parent.verticalCenter
            x: 95
            radius: 4
            text: "pathView"
            onClicked: {
                pathView.visible = true
                rowView.visible = false
            }
        }
        RoundButton {
            width: 120
            height: 40
            anchors.verticalCenter: parent.verticalCenter
            x: 515
            radius: 4
            text: "Open folder"
            onClicked: folderDialog.open();

        }
        FolderDialog {
            id: folderDialog
            currentFolder: ""
            folder: StandardPaths.standardLocations(StandardPaths.PicturesLocation)[0]
            onFolderChanged: {
                folderModel.folder = folder;
            }
        }
    }
    Rectangle {
        id: root
        y:25
        width: parent.width
        height: parent.height
        clip: true
        PathView {
            id: pathView
            visible: false;
            anchors.fill: parent
            model: folderModel
            delegate: myDelegate
            dragMargin: 300
            snapMode: PathView.SnapToItem
            maximumFlickVelocity: width
            preferredHighlightBegin:0.5
            preferredHighlightEnd:0.5
            clip: true
            path: Path {
                id:flowViewPath
                readonly property real yCoord: pathView.height/2
                startX: 0
                startY: flowViewPath.yCoord
                PathAttribute{name:"elementZ"; value: 0}
                PathAttribute{name:"elementScale"; value: 0.3}
                PathLine {
                    x: pathView.width*0.5
                    y: flowViewPath.yCoord
                }
                PathAttribute{name:"elementZ";value:100}
                PathAttribute{name:"elementScale";value:1.0}
                PathLine {
                    x: pathView.width
                    y: flowViewPath.yCoord
                }
                PathAttribute{name:"elementZ";value:0}
                PathAttribute{name:"elementScale";value:0.3}
                PathPercent{value:1.0}
            }
        }
        Component {
            id: myDelegate
            Image {
                width: 500; height: 400
                fillMode: Image.PreserveAspectCrop
                scale: PathView.elementScale
                z: PathView.elementZ
                source: fileURL
                MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            if(parent.width === 640){
                                parent.width = 500
                            }
                            else{
                                parent.width = 640
                            }

                            if(parent.height === 430){
                                parent.height = 400
                            }
                            else{
                                parent.height = 430
                            }

                        }
                    }
            }
        }
        ListModel {
            id: myModel
            ListElement  {modelColor: "red"}
            ListElement  {modelColor: "green"}
            ListElement  {modelColor: "blue"}
            ListElement  {modelColor: "yellow"}
            ListElement  {modelColor: "orange"}
        }
        FolderListModel {
            id: folderModel
            nameFilters: ["*.png", "*.jpg", "*.bmp", "*.jpeg", "*.tiff"]
            folder: "file:///D:/Programming/Qt/Desktop_mobile_GUI/img"
        }
        Row {
            id:rowView
            y:25
            ListView {
                id:listView
                width: 640
                height: 300
                Component {
                    id: fileDelegate
                    Column {
                        Image {
                            width: 640
                            fillMode: Image.PreserveAspectFit
                            smooth: true
                            source: fileURL
                        }
                    }
                }
                model: folderModel
                delegate: fileDelegate
            }
            GridView {
                id:gridView
                visible:false
                width: 640
                height: 430
                Component {
                    id: gridfileDelegate
                    Column {
                        Image {
                            width: 100;
                            height: 100
                            fillMode: Image.PreserveAspectCrop
                            source: fileURL
                            /*MouseArea{
                                anchors.fill: parent;
                                onClicked: {
                                    parent.width = 400;
                                    parent.width = 400;
                                }
                            }*/

                            /*onScaleChanged: {
                                console.debug(scale)
                                if ((width * scale) > f.width) {
                                    var xoff = (f.width / 2 + f.contentX) * scale / prevScale;
                                    f.contentX = xoff - f.width / 2
                                }
                                if ((height * scale) > f.height) {
                                    var yoff = (f.height / 2 + f.contentY) * scale / prevScale;
                                    f.contentY = yoff - f.height / 2
                                }
                                prevScale=scale;
                            }
                            onStatusChanged: {
                                if (status===Image.Ready) {
                                    f.fitToScreen();
                                }
                            }*/
                        }
                    }
                }
                model: folderModel
                delegate: gridfileDelegate
            }
        }
    }
}
