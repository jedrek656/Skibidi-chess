import QtQuick 2.15

Rectangle {
    id: root
    width: 100
    height: 108
    radius: width
    color: Qt.rgba(0,0,0,0)

    Rectangle {
        width: parent.width * 0.9
        height: parent.height * 0.9
        anchors.centerIn: parent
        radius: width
        border.width: 0.2 * width
        border.color: Qt.rgba(0.4, 0, 1, 0.7)
        color: Qt.rgba(0, 0, 0, 0)
    }
}
