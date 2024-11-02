

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick
import QtQuick.Controls
import Skibidi

Rectangle {
    id: rectangle
    width: Screen.width
    height: Screen.height
    color: "#302E2B"

    Chessboard {
        id: chessboard
        anchors.verticalCenter: parent.verticalCenter
        x: 0.02 * parent.width
        width: parent.height * 0.8
        height: parent.height * 0.8

        ChessPiece {
            id: chessPiece
            x: 443
            y: 528
            width: parent.width / 10
            height: parent.height / 10
        }

        PossibleMoveCircle {
            id: possibleMoveCircle
            x: 454
            y: 450
            width: parent.width / 15
            height: parent.height / 15
        }
    }

    MyTimer {
        id: myTimer
        anchors.bottom: chessboard.top
        anchors.bottomMargin: parent.height * 0.01
        anchors.left: chessboard.left
        width: chessboard.width / 3
        height: chessboard.height / 14
    }

    MyTimer {
        id: myTimer1
        anchors.top: chessboard.bottom
        anchors.topMargin: parent.height * 0.01
        anchors.left: chessboard.left
        width: chessboard.width / 3
        height: chessboard.height / 14
    }

    BrainrotVideo {
        id: brainrotVideo
        anchors.top: descripition.top
        anchors.left: descripition.right
        anchors.leftMargin: parent.width * 0.02
        width: parent.width * 0.2
        height: descripition.height
    }

    Descripition {
        id: descripition
        anchors.top: myTimer.top
        anchors.left: chessboard.right
        anchors.leftMargin: parent.width * 0.03
        width: parent.width / 4
        height: parent.height / 1.4
    }

    ManaBar {
        id: manaBar
        anchors.right: chessboard.right
        anchors.top: myTimer.top
        width: chessboard.width / 1.5
        height: myTimer.height
    }

    ManaBar {
        id: manaBar1
        anchors.right: chessboard.right
        anchors.top: myTimer1.top
        width: chessboard.width / 1.5
        height: myTimer1.height
    }

    SettingsButton {
        id: settingsButton
        anchors.right: brainrotVideo.right
        anchors.top: spell.top
        width: spell.width
        height: spell.height
    }

    Spell {
        id: spell1
        anchors.left: descripition.left
        anchors.bottom: chessboard.bottom
        width: descripition.width / 3.3
        height: descripition.width / 3.3
    }

    Spell {
        id: spell
        anchors.horizontalCenter: descripition.horizontalCenter
        anchors.bottom: chessboard.bottom
        width: descripition.width / 3.3
        height: descripition.width / 3.3
    }

    Spell {
        id: spell2
        anchors.right: descripition.right
        anchors.bottom: chessboard.bottom
        width: descripition.width / 3.3
        height: descripition.width / 3.3
    }

    /*MenuSettings {
        id: menuSettings
        visible: false
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        width: 800
        height: 1000
    }*/

    MainMenu {
        id: mainMenu
        x: 0
        y: 0
        visible: true
    }
}
