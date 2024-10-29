import QtQuick
import QtQuick.Controls

Rectangle {

    property string name: "Asbest"
    property int cost: 3

    id: root
    width: 200
    height: 200
    color: "black"
    Rectangle {
        width: 0.8 * root.width
        height: 0.8 * root.height
        x: 0.1 * root.width
        y: 0.1 * root.height
        Text{
            text: cost
            width: 0.3 * parent.width
            height: 0.3 * parent.height
            font.pointSize: 100
            minimumPointSize: 10
            fontSizeMode: Text.Fit
        }
        Text{
            text: name
            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 100
            minimumPointSize: 10
            fontSizeMode: Text.Fit
        }
    }
}
