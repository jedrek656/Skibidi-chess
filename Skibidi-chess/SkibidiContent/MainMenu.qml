import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    anchors.fill: parent
    color: "black"
    id: root

    property string activeTextColor: "#874a12"


    Image {
        id: skibidiToiletOriginal
        x: parent.width*0.07
        y: parent.height*0.27
        width: parent.width*0.21
        height: parent.height*0.57
        source: "images/skibidi-toilet-original.png"
        rotation: -10
        fillMode: Image.PreserveAspectFit
    }
    Image {
        id: _30MediumToilet
        x: parent.width*0.7
        y: parent.height*0.47
        width: parent.width*0.26
        height: parent.height*0.5
        source: "images/30-MediumToilet.png"
        fillMode: Image.PreserveAspectFit
    }
    Image {
        id: normalToiletImage
        x: parent.width*0.58
        y: parent.height*0.055
        width: parent.width*0.13
        height: parent.height*0.33
        source: "images/NormalToiletImage.png"
        fillMode: Image.PreserveAspectFit
    }

    FontLoader{
        id: trajan
        source: "fonts/TrajanPro-Regular.ttf"
    }

    Text {
        text: "SKIBIDI CHESS"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: parent.height * 0.27
        font.pixelSize: parent.width*0.1
        font.family: trajan.font.family
        font.weight: trajan.font.weight
        font.styleName: trajan.font.styleName
        //font.family: "Vtks Demolition"
        color: "white"
        font.bold: true
        style:Text.Outline
        styleColor:"black"
    }
    Column {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: parent.height * 0.6
        spacing: parent.height * 0.02

        Button {
            text: "NEW GAME"
            font.pixelSize: parent.height*0.12
            anchors.horizontalCenter: parent.horizontalCenter
            font.family: "Serif"
            font.bold: true
            background: Rectangle {
                color: "black"
                radius: 10
            }
            palette.buttonText: hovered ? root.activeTextColor : "white"
            onClicked: ChessboardObj.loadPosition();
        }

        Button {
            text: "LOAD"
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: parent.height*0.12
            font.family: "Serif"
            font.bold: true
            background: Rectangle {
                color: "black"
                radius: 10
            }
            palette.buttonText: hovered ? root.activeTextColor : "white"
            onClicked: GameObj.openLoadDialog()
        }

        Button {
            text: "OPTIONS"
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: parent.height*0.12
            font.family: "Serif"
            font.bold: true
            background: Rectangle {
                color: "black"
                radius: 10
            }
            palette.buttonText: hovered ? root.activeTextColor : "white"
            onClicked: GameObj.openSettings()
        }

        Button {
            text: "QUIT"
            //id: quitButton
            //text: ChessboardObj.getNumOfPieces()
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: parent.height*0.12
            font.family: "Serif"
            font.bold: true
            background: Rectangle {
                color: "black"
                radius: 10
            }
            palette.buttonText: hovered ? root.activeTextColor : "white"
            onClicked: GameObj.closeApp()
        }
    }

    Text {
        id: _text
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: parent.height*0.0185
        font.pixelSize: parent.height*0.023
        color:"gray"
        text: qsTr("Przegrałem w grę")
    }

    Connections{
        target: ChessboardObj
        onChessboardLoaded: {
            root.visible = false;
        }
    }
}
