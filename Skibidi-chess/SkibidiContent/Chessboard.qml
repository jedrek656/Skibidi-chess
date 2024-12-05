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
                ChessboardObj.setActivePiece(-1);
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
                    if (root.isActive == false && isWhite == GameObj.checkTurn()) {
                        var possibleMoves = ChessboardObj.getPossibleMoves(index)
                        possibleMovesRepeater.possibleMoves = possibleMoves
                        ChessboardObj.setActivePiece(index);
                        root.isActive = true
                    }
                    else if (ChessboardObj.getActivePiece() != index && isWhite == GameObj.checkTurn()) {
                        var possibleMoves = ChessboardObj.getPossibleMoves(index)
                        possibleMovesRepeater.possibleMoves = possibleMoves
                        ChessboardObj.setActivePiece(index);
                    }
                    else {
                        possibleMovesRepeater.possibleMoves = []
                        ChessboardObj.setActivePiece(-1);
                        root.isActive = false
                    }
                }
            }
        }
    }

    Repeater {
        id: possibleMovesRepeater
        property variant possibleMoves: []

        function move(index) {
            if (ChessboardObj.getActivePiece() != -1){
                switch(possibleMovesRepeater.possibleMoves[index][2]){
                    case 0:
                        ChessboardObj.movePiece(ChessboardObj.getActivePiece(),
                                                possibleMovesRepeater.possibleMoves[index][0],
                                                possibleMovesRepeater.possibleMoves[index][1]);
                        break;
                    case 1:
                        ChessboardObj.capturePiece(ChessboardObj.getActivePiece(),
                                                   possibleMovesRepeater.possibleMoves[index][0],
                                                   possibleMovesRepeater.possibleMoves[index][1]);
                        break;
                    case 2:
                        ChessboardObj.enPassant(ChessboardObj.getActivePiece(),
                                                   possibleMovesRepeater.possibleMoves[index][0],
                                                   possibleMovesRepeater.possibleMoves[index][1]);
                        break;
                    case 3:
                        ChessboardObj.castling(ChessboardObj.getActivePiece(),
                                                   possibleMovesRepeater.possibleMoves[index][0],
                                                   possibleMovesRepeater.possibleMoves[index][1]);
                        break;
                }
                ChessboardObj.setActivePiece(-1);
                possibleMovesRepeater.possibleMoves = []
                root.isActive = false
            }
        }

        function executeTurn(index) {
            possibleMovesRepeater.move(index)
            GameObj.changeTurn()
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
                anchors.fill: parent
                sourceComponent: {
                        switch (possibleMovesRepeater.possibleMoves[index][2]) {
                            case 0:
                                return moveIcon;
                                break;
                            case 1:
                            case 2:
                                return captureIcon;
                                break;
                            case 3:
                            case 4:
                                return moveIcon;
                                break;
                            default:
                                return moveIcon;
                                break;
                        }
                    }
            }

            Button{
                anchors.fill: parent
                background: Rectangle{color: Qt.rgba(0,0,0,0)}
                onClicked: {
                    possibleMovesRepeater.executeTurn(index)
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

    Repeater{
        model: SpellListObj
        Asbestos{
            width: 3 * root.width / 8
            height: 3 * root.height / 8
            x: 4 * root.width/8
            y: 4 * root.height/8
        }
    }

    Repeater{

        id: possibleSpellsRepeater
        property variant possibleSpells: []
        model: possibleSpells.length
        Rectangle{
            required property int index
            width: root.width / 8
            height: root.height / 8
            x: possibleSpellsRepeater.possibleSpells[index][0] * root.width / 8  + (root.width / 16 - width / 2)
            y: possibleSpellsRepeater.possibleSpells[index][1] * root.height / 8 + (root.height / 16 - height / 2)
            color: Qt.rgba(0,0,0,0)

            Button{
                anchors.fill: parent
                background: Rectangle{color: Qt.rgba(0,0,0,0)}
                onClicked: {

                }
            }

            PossibleSpellCircle{
                anchors.fill: parent
            }
        }
    }

    Connections{
        target: ChessboardObj
        onSpellFieldsGenerated: (fields) => {
            possibleSpellsRepeater.possibleSpells = fields
        }
    }
}
