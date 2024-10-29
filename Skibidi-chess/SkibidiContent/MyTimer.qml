import QtQuick
import QtQuick.Controls

Rectangle {
    id: root
    width: 300
    height: 100

    radius: 0.04 * width

    color: "black"

    Text {
        anchors.fill: parent
        text: "21:37"
        color: "white"
        font.family: "Comic Sans MS"

        font.pointSize: 100
        minimumPointSize: 10
        fontSizeMode: Text.Fit
    }
}
