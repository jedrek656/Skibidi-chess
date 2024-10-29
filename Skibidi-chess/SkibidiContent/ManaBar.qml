import QtQuick
import QtQuick.Controls

Item {
    id: root
    width: 600
    height: 100

    property int manaPoints: 8
    property int maxMana: 10

    property string grayDark: "gray"
    property string grayLigt: "darkgray"

    property string blueDark: "#0290a6"
    property string blueLight: "#12dfff"

    Rectangle{
        width: 5/6 * root.width
        height: root.height / 2
        anchors.right: root.right
        id: manaBar
        anchors.verticalCenter: root.verticalCenter
        Repeater{
            model: maxMana
            Rectangle{
                required property int index
                Rectangle{
                    anchors.fill: parent
                    gradient: Gradient {
                        GradientStop { position: 0.8; color: grayLigt }
                        GradientStop { position: 1.0; color: grayDark }
                    }
                }
                Rectangle{
                    anchors.fill: parent
                    gradient: Gradient {
                        orientation: Gradient.Horizontal
                        GradientStop { position: 0.8; color: Qt.rgba(0, 0, 0, 0) }
                        GradientStop { position: 1.0; color: grayDark }
                    }
                }
                height: 0.8 *  manaBar.height
                width: 0.9 *  (manaBar.width / maxMana)
                x: (index) * manaBar.width / maxMana
                y: 0.1*manaBar.height
            }
        }

        Repeater{
            model: manaPoints
            Rectangle{
                required property int index
                Rectangle{
                    anchors.fill: parent
                    gradient: Gradient {
                        GradientStop { position: 0.8; color: blueLight }
                        GradientStop { position: 1.0; color: blueDark }
                    }
                }
                Rectangle{
                    anchors.fill: parent
                    gradient: Gradient {
                        orientation: Gradient.Horizontal
                        GradientStop { position: 0.8; color: Qt.rgba(0, 0, 0, 0) }
                        GradientStop { position: 1.0; color: blueDark }
                    }
                }
                height: 0.8 *  manaBar.height
                width: 0.9 *  (manaBar.width / maxMana)
                x: (index) * manaBar.width / maxMana
                y: 0.1*manaBar.height
            }
        }
    }

    Rectangle{
        id: manaCrystal
        anchors.verticalCenter: root.verticalCenter
        width: 0.75 * root.height
        height: 0.75 * root.height
        anchors.horizontalCenter: manaBar.left
        anchors.horizontalCenterOffset: -width / 4
        rotation: -45
        radius: width / 6
        color: blueLight
        border.width: width * 0.1
        border.color:  "#000f12"
    }

}
