import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: root
    width: 800
    height: 800
    color: "black"
    opacity: 0.8
    visible: true
    property var pieceIdx: -1;
    ChessPiece {
        id: qChessPiece
        width: root.width / 5
        height: root.height / 5
        name: "Queen";
        isWhite: true;
        x: root.width/4
        y: root.height/4
        Button{
            anchors.fill: parent
            background: Rectangle{color: Qt.rgba(0,0,0,0)}
            onClicked: {
                ChessboardObj.promotePiece(pieceIdx, "Queen")
                root.visible = false;
            }
        }
    }
    ChessPiece {
        id: rChessPiece
        width: root.width / 5
        height: root.height / 5
        name: "Rook";
        isWhite: true;
        x: root.width/4 + rChessPiece.width + root.width/16
        y: root.height/4
        Button{
            anchors.fill: parent
            background: Rectangle{color: Qt.rgba(0,0,0,0)}
            onClicked: {
                ChessboardObj.promotePiece(pieceIdx, "Rook")
                root.visible = false;
            }
        }
    }
    ChessPiece {
        id: bChessPiece
        width: root.width / 5
        height: root.height / 5
        name: "Bishop";
        isWhite: true;
        x: root.width/4
        y: root.height/4 + bChessPiece.height + root.height/16
        Button{
            anchors.fill: parent
            background: Rectangle{color: Qt.rgba(0,0,0,0)}
            onClicked: {
                ChessboardObj.promotePiece(pieceIdx, "Bishop")
                root.visible = false;
            }
        }
    }
    ChessPiece {
        id: kChessPiece
        width: root.width / 5
        height: root.height / 5
        name: "Knight";
        isWhite: true;
        x: root.width/4 + kChessPiece.width + root.width/16
        y: root.height/4 + kChessPiece.height + root.height/16
        Button{
            anchors.fill: parent
            background: Rectangle{color: Qt.rgba(0,0,0,0)}
            onClicked: {
                ChessboardObj.promotePiece(pieceIdx, "Knight")
                root.visible = false;
            }
        }
    }
    Connections {
        target: ChessboardObj
        onPromotionDialog: {
            qChessPiece.isWhite = isWhite;
            rChessPiece.isWhite = isWhite;
            bChessPiece.isWhite = isWhite;
            kChessPiece.isWhite = isWhite;
            root.pieceIdx = idx;
            root.visible = true;
        }
        onChessboardLoaded: {
            root.visible = false
        }
    }
}
