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
        id: chessPiecesRepeater
        model: ChessboardObj.getNumOfPieces()
        ChessPiece {
            id: chessPiece
            required property int index
            property var pieceData: ChessboardObj.getPiece(index)
            width: root.width / 10
            height: root.height / 10
            name: pieceData[0]
            isWhite: pieceData[3]
            x: pieceData[1] * root.width / 8 + (root.width / 16 - width / 2)
            y: pieceData[2] * root.height / 8 + (root.height / 16 - height / 2)
            Button{
                anchors.fill: parent
                background: Rectangle{color: Qt.rgba(0,0,0,0)}
                onClicked: {
                    var possibleMoves = ChessboardObj.getPossibleMoves(index)
                    possibleMovesRepeater.possibleMoves = possibleMoves
                    possibleMovesRepeater.activePiece = index
                }
            }
        }
    }

    Repeater {
        id: possibleMovesRepeater
        property variant possibleMoves: []
        property int activePiece: -1
        model: possibleMoves.length
        PossibleMoveCircle{
            required property int index
            width: root.width / 14
            height: root.height / 14
            x: possibleMovesRepeater.possibleMoves[index][0] * root.width / 8  + (root.width / 16 - width / 2)
            y: possibleMovesRepeater.possibleMoves[index][1] * root.height / 8 + (root.height / 16 - height / 2)
            Button{
                anchors.fill: parent
                background: Rectangle{color: Qt.rgba(0,0,0,0)}
                onClicked: {
                    ChessboardObj.movePiece(possibleMovesRepeater.activePiece, possibleMovesRepeater.possibleMoves[index][0], possibleMovesRepeater.possibleMoves[index][1])
                    possibleMovesRepeater.activePiece = -1
                    possibleMovesRepeater.possibleMoves = []
                    chessPiecesRepeater.model = ChessboardObj.getNumOfPieces()
                }
            }
        }
    }
}
