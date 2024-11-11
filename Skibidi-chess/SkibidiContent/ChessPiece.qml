import QtQuick
import QtQuick.Controls

Rectangle {

    property string name: "aaa"
    property bool isWhite: true;

    id: root
    width: 200
    height: 200
    color: "black"
    Rectangle {
        width: 0.8 * root.width
        height: 0.8 * root.height
        x: 0.1 * root.width
        y: 0.1 * root.height
        color: root.isWhite ? "white" : "black"
        Text{
            text: root.name
            color: root.isWhite ? "black" : "white"
            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 100
            minimumPointSize: 10
            fontSizeMode: Text.Fit
        }
    }
}
