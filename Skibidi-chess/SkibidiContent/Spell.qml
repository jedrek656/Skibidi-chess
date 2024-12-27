import QtQuick
import QtQuick.Controls

Rectangle {

    property string name: "Asbestos"
    property int cost: 3
    property int index: 0

    id: root
    width: 200
    height: 200
    color: "black"
    Rectangle {
        width: 0.8 * root.width
        height: 0.8 * root.height
        x: 0.1 * root.width
        y: 0.1 * root.height
        Text{
            text: root.cost
            width: 0.3 * parent.width
            height: 0.3 * parent.height
            font.pointSize: 100
            minimumPointSize: 10
            fontSizeMode: Text.Fit
        }
        Text{
            text: root.name
            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 100
            minimumPointSize: 10
            fontSizeMode: Text.Fit
        }
        MouseArea{
            property bool activeChoice: false
            anchors.fill: parent
            hoverEnabled: true
            onEntered: {
                SpellListObj.setActiveSpell(index)
                ChessboardObj.getPossibleSpellFields(index, GameObj.checkTurn())
            }
            onExited: {
                if (!activeChoice){
                    SpellListObj.setActiveSpell(-1)
                    ChessboardObj.resetPossibleSpellFields()
                }
            }
            onClicked: {
                activeChoice = !activeChoice
            }
        }
    }
}
