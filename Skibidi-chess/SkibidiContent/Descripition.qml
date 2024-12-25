import QtQuick
import QtQuick.Controls

Rectangle {
    id: rectangle
    width: 500
    height: 400

    color: "lightgray"

    Text {
        id: label
        x: parent.width * 0.05
        y: parent.height * 0.05
        width: 124
        height: 93
        text: "Skibidi sigma ohio"
        font.bold: true
        //font.pointSize: parent.height * 0.07
        font.pointSize: 28
    }

    Text {
        id: description
        x: parent.width * 0.05
        y: parent.height * 0.2
        width: parent.width * 0.5
        height: parent.height * 0.8
        text: ""
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignTop
        wrapMode: Text.WordWrap
        font.italic: false
        //font.pointSize: parent.height * 0.05
        font.pointSize: 20
    }

    Connections{
        target: SpellListObj
        onActiveSpellChanged: (index) => {
            switch(index){
                case 0:
                    description.text = "By spitting on that thang (your piece) you are able to make it uncaputrable for one round. However you can't move this piece this round."
                    break;
                case 1:
                    description.text = "Pouring the fresh asbesto on ground makes every piece..."
                    break;
                case 2:
                    description.text = "The drippy cheese (found only in newest lunchly) works as blank piece bloking the moves for both sides."
                    break;
                case -1:
                    description.text = "Hover over spell to read its description :33"
                    break;
            }
        }
    }
}
