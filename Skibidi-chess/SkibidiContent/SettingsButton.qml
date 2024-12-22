import QtQuick
import QtQuick.Controls

/*Item {
    id: root
    width: 200
    height: 100

    Button{
        anchors.fill: parent
        text: "SETTINGS"
        font.pixelSize: root.width * 0.2
    }
}*/

Rectangle {
    id: root
    width: 200
    height: 200

    gradient: Gradient {
        GradientStop { position: 0.9; color: "darkgray" }
        GradientStop { position: 1.0; color: "gray" }
    }

    Rectangle{
        anchors.fill: parent
        gradient: Gradient {
            orientation: Gradient.Horizontal
            GradientStop { position: 0.9; color: Qt.rgba(0,0,0,0) }
            GradientStop { position: 1.0; color: "gray" }
        }
    }

    property int size: Math.min(width, height)

    function getCircularPosition(centerX, centerY, radius, angle){
        var radians = angle
        return [centerX + radius * Math.cos(radians), centerY + radius * Math.sin(radians)]
    }

    Canvas{
        id: mycanvas
        anchors.fill: parent
        onPaint: {
            var ctx = getContext("2d");
            ctx.reset()
            for(var i = 0; i < 8; i++){
                ctx.arc(width/2, height/2, 0.3 * size, Math.PI / 8 * (2*i + 0.5), Math.PI / 8 * (2*i + 1.5), false)
                let [upX, upY] = getCircularPosition(width / 2, height / 2, 0.4 * size, Math.PI / 8 * (2*i+1.7))
                let [rightX, rightY] = getCircularPosition(width / 2, height / 2, 0.4 * size, Math.PI / 8 * (2*i+2.3))
                let [newX, newY] = getCircularPosition(width / 2, height / 2, 0.3 * size, Math.PI / 8 * (2*i+2.5))
                ctx.lineTo(upX, upY)
                ctx.lineTo(rightX, rightY)
                ctx.lineTo(newX, newY)
            }
            ctx.arc(width / 2, height / 2, 0.15 * size, 0, Math.PI * 2, true)
            ctx.stroke()
            ctx.fill()
        }
    }

    Button{
        anchors.fill: parent
        onClicked: GameObj.pauseGame();
        background:
            Rectangle{
                anchors.fill: parent;
                color: Qt.rgba(0,0,0,0);
            }
    }
}
