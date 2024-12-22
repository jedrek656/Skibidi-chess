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
            y: root.height/10
            color: "#ffffff"
            text: qsTr("Settings")
            font.family: "Verdana"
            font.bold: true

        }

        Slider{
            anchors.horizontalCenter: parent.horizontalCenter
            y: root.height / 3.5
            width: root.width / 2.8
            height: root.height / 10

        }

        Button {
            id: button
            x: root.width/3
            y: root.height/2.5
            width: root.width/3
            height: root.height/8
            text: qsTr("LOAD")
            font.pixelSize: 80
            font.family: "Verdana"
            icon.color: "#27262a"

            onClicked: GameObj.openLoadDialog();
        }

        Button {
            id: button2
            x: root.width/3
            y: root.height/2.5 + root.height/6
            width: root.width/3
            height: root.height/8
            text: qsTr("SAVE")
            font.pixelSize: 80
            font.family: "Verdana"
            icon.color: "#27262a"

            onClicked: GameObj.openSaveDialog();
        }

        Button {
            id: button3
            x: root.width/3
            y: root.height/2.5 + root.height/3
            width: root.width/3
            height: root.height/8
            text: qsTr("EXIT")
            font.pixelSize: 80
            font.family: "Verdana"
            icon.color: "#27262a"

            onClicked: GameObj.closeApp();
        }
    }

    Connections{
        target: GameObj;
        onGamePaused: root.visible = !root.visible;
    }
}
