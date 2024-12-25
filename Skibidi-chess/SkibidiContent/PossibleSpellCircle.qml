import QtQuick 2.15
import QtQuick.Controls

Rectangle {
    id: root;
    width: 100;
    height: 108;
    radius: width;
    color: Qt.rgba(0,0,0,0);

    property int posX;
    property int posY;

    Rectangle {
        width: parent.width * 0.9;
        height: parent.height * 0.9;
        anchors.centerIn: parent;
        radius: width;
        border.width: 0.2 * width;
        border.color: Qt.rgba(0.4, 0, 1, 0.7);
        color: Qt.rgba(0, 0, 0, 0);
    }

    Button {
        anchors.fill: parent;
        background:
            Rectangle{
                anchors.fill: parent;
                color: Qt.rgba(0,0,0,0);
            }
        onClicked: SpellListObj.castSpell(root.posX, root.posY, SpellListObj.getActiveSpell());
    }
}
