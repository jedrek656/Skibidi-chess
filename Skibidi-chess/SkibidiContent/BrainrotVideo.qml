import QtQuick
import QtQuick.Controls

import QtMultimedia

Rectangle {
    id: root
    width: 450
    height: 800

    color: "red"

    Video {
        id: video
        width : root.width
        height : root.height
        source: "brainrrot.mp4"

        fillMode: VideoOutput.Stretch

        MouseArea {
            anchors.fill: parent
            onClicked: {
                //video.play()
                //ChessboardObj.loadPosition();
                SpellListObj.test();
            }
        }
    }
}
