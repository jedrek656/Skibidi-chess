import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: root
    width: 800
    height: 800
    color: "black"
    opacity: 0.8
    visible: true

    Text {
        id: messageText
        width: parent.width * 0.8
        height: parent.height * 0.2
        anchors.horizontalCenter: parent.horizontalCenter
        horizontalAlignment: Text.AlignHCenter
        font.pointSize: 9999999
        minimumPointSize: 10
        fontSizeMode: Text.Fit
        y: parent.height/3
        color: "white"
        font.pixelSize: parent.width * 0.6
        text: "Default Message"
    }
    Connections {
        target: ChessboardObj
        onGameEnd: {
            messageText.text = message + " has won!";
            root.visible = true;
        }
        onChessboardLoaded: {
            root.visible = false
        }
    }
}
