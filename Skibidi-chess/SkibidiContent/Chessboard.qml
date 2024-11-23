import QtQuick
import QtQuick.Controls

Item {

    property string colorA: "#EBECD0"
    property string colorB: "#779556"

    id: root
    width: 800
    height: 800
    property bool isActive: false   // active = possible moves should be displayed

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

    Button {
        anchors.fill: parent
        background: Rectangle{color: Qt.rgba(0,0,0,0)}
        onClicked: {
            if (root.isActive == true) {
                possibleMovesRepeater.possibleMoves = []
                possibleMovesRepeater.activePiece = -1
                root.isActive = false
            }
        }
    }

    Repeater {
        id: chessPiecesRepeater
        model: ChessboardObj
        ChessPiece {
            id: chessPiece
            required property string nameProperty
            required property int posX
            required property int posY
            required property bool isWhiteProperty
            required property string index
            width: root.width / 10
            height: root.height / 10
            name: nameProperty
            isWhite: isWhiteProperty
            x: posX * root.width / 8 + (root.width / 16 - width / 2)
            y: posY * root.height / 8 + (root.height / 16 - height / 2)
            Button{
                anchors.fill: parent
                background: Rectangle{color: Qt.rgba(0,0,0,0)}
                onClicked: {
                    if (root.isActive == false) {
                        var possibleMoves = ChessboardObj.getPossibleMoves(index)
                        possibleMovesRepeater.possibleMoves = possibleMoves
                        possibleMovesRepeater.activePiece = index
                        root.isActive = true
                    }
                    else if (possibleMovesRepeater.activePiece != index) {
                        var possibleMoves = ChessboardObj.getPossibleMoves(index)
                        possibleMovesRepeater.possibleMoves = possibleMoves
                        possibleMovesRepeater.activePiece = index
                    }
                    else {
                        possibleMovesRepeater.possibleMoves = []
                        possibleMovesRepeater.activePiece = -1
                        root.isActive = false
                    }
                }
            }
        }
    }

    Repeater {
        id: possibleMovesRepeater
        property variant possibleMoves: []
        property int activePiece: -1

        function move(index) {
            if (possibleMovesRepeater.activePiece != -1){
                if(possibleMovesRepeater.possibleMoves[index][2]) {
                    ChessboardObj.capturePiece(possibleMovesRepeater.activePiece, possibleMovesRepeater.possibleMoves[index][0], possibleMovesRepeater.possibleMoves[index][1])
                }
                else{
                    ChessboardObj.movePiece(possibleMovesRepeater.activePiece, possibleMovesRepeater.possibleMoves[index][0], possibleMovesRepeater.possibleMoves[index][1])
                }
                possibleMovesRepeater.activePiece = -1
                possibleMovesRepeater.possibleMoves = []
                root.isActive = false
            }
        }

        model: possibleMoves.length
        Rectangle{
            required property int index
            width: root.width / 8
            height: root.height / 8
            x: possibleMovesRepeater.possibleMoves[index][0] * root.width / 8  + (root.width / 16 - width / 2)
            y: possibleMovesRepeater.possibleMoves[index][1] * root.height / 8 + (root.height / 16 - height / 2)
            color: Qt.rgba(0,0,0,0)

            Loader {
                anchors.centerIn: parent
                width: parent.width
                height: width
                sourceComponent: possibleMovesRepeater.possibleMoves[index][2]
                    ? captureIcon
                    : moveIcon
            }

            Button{
                anchors.fill: parent
                background: Rectangle{color: Qt.rgba(0,0,0,0)}
                onClicked: {
                    possibleMovesRepeater.move(index)
                }
            }

            Component {
                id: captureIcon
                PossibleCaptureIcon {
                    anchors.fill: parent
                }
            }

            Component {
                id: moveIcon
                PossibleMoveCircle {
                    anchors.fill: parent
                    anchors.margins: parent.width * 0.3
                }
            }
        }
    }

    /*Connections{
        target: ChessboardObj
        function onChangePlayer() {
        }
    }*/
}
