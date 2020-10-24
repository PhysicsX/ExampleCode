import QtQuick 2.12
import QtQuick.Window 2.12
import QtMultimedia 5.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Rectangle {
        width: 800
        height: 600
        color: "black"

        MediaPlayer {
            id: player
            //source: "file:///home/jnano/Desktop/build-VideoOutput-Desktop-Release/file_example_WEBM_480_900KB.webm"
            source: "file:///home/ulas/Desktop/file_example_WEBM_1920_3_7MB.webm"
            autoPlay: true
        }

        VideoOutput {
            id: videoOutput
            source: player
            anchors.fill: parent
        }
    }
}
