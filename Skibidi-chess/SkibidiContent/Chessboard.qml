import QtQuick
import QtQuick.Controls

Item {

    property string colorA: "#EBECD0"
    property string colorB: "#779556"

    id: root
    width: 800
    height: 800

    Repeater {
        model: 8
        Repeater {
            required property int index
            property int idx1: index
            model: 8
            Rectangle {
                required property int index
                width: root.width / 8
                height: root.height / 8
                color: (idx1 + index)%2 == 0 ? colorA : colorB
                x: index * root.width/8
                y: idx1 * root.height/8
            }
        }
    }

    Repeater {
        model: ChessboardObj.getNumOfPieces()
        ChessPiece {
            required property int index
            width: root.width / 10
            height: root.height / 10
            x: index * root.width / 8

        }
    }
}
