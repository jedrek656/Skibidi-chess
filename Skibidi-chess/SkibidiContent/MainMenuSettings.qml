import QtQuick
import QtQuick.Controls

Item {
    id: root
    width: 800
    height: 1000
    visible: false

    Rectangle {
        id: rectangle
        x: 0
        y: 0
        width: root.width
        height: root.height
        color: "#303030"

        Text {
            id: _text
            width: parent.width * 0.8
            height: parent.height * 0.2
            anchors.horizontalCenter: parent.horizontalCenter
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 100
            minimumPointSize: 10
            fontSizeMode: Text.Fit
            y: root.height / 30
            color: "#ffffff"
            text: qsTr("Settings")
            font.family: "Verdana"
            font.bold: true
        }

        Text {
            id: sliderLabel
            width: root.width / 2
            height: root.height / 6
            anchors.horizontalCenter: parent.horizontalCenter
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 70
            minimumPointSize: 10
            fontSizeMode: Text.Fit
            y: root.height / 3
            color: "#ffffff"
            text: qsTr("VOLUME")
            font.family: "Verdana"
        }

        Slider{
            anchors.horizontalCenter: parent.horizontalCenter
            y: root.height / 2.25
            width: root.width / 2.8
            height: root.height / 10

        }

        Button {
            id: button
            x: root.width / 3
            y: root.height / 1.5
            width: root.width / 3
            height: root.height / 8
            text: qsTr("BACK")
            font.pixelSize: 80
            font.family: "Verdana"
            icon.color: "#27262a"
            onClicked: root.visible = false
        }
    }

    Connections{
        target: GameObj;
        onMenuPaused: root.visible = !root.visible;
    }
}
