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

    Image {
        id: image
        x: parent.width * 0.55
        y: parent.height * 0.2
        width: parent.width * 0.4
        height: parent.height * 0.8
        source: "qrc:/qtquickplugin/images/template_image.png"
        fillMode: Image.PreserveAspectFit
    }

    Connections{
        target: SpellListObj
        onActiveSpellChanged: (index) => {
            switch(index){
                case 0:
                    description.text = "spit on that thing"
                    break;
                case 1:
                    description.text = "mmmm Asbesto"
                    break;
                case 2:
                    description.text = "..."
                    break;
                case -1:
                    description.text = ""
                    break;
            }
        }
    }
}
