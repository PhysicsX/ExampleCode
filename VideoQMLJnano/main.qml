import QtQuick 2.12
import QtQuick.Window 2.12
import QtMultimedia 5.12
import QtQuick.Controls.Styles 1.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Rectangle {
        width: 800
        height: 480
        color: "black"

        MediaPlayer {
            id: player
            //source: "gst-pipeline: videotestsrc ! qtvideosink"
            //source: "gst-pipeline: playbin uri=https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_trailer-480p.webm"
            source: "gst-pipeline: nvarguscamerasrc ! video/x-raw,width=800,height480 ! autovideoconvert ! qtvideosink"
            //source: "file:///home/jnano/Desktop/build-VideoOutput-Desktop-Release/file_example_WEBM_480_900KB.webm"
            //source: "file:///home/ulas/Desktop/file_example_WEBM_1920_3_7MB.webm"
            autoPlay: true
        }

        VideoOutput {
            id: videoOutput
            source: player
            anchors.fill: parent
        }
        Item {
          y: 300;
          property string text: " this is Qt streaming! "
          property string spacing: "      "
          property string combined: text + spacing + text
          property string display: combined.substring(step) + combined.substring(0, step)
          property int step: 0

          Timer {
            interval: 200
            running: true
            repeat: true
            onTriggered: parent.step = (parent.step + 1) % parent.combined.length
          }

          Text {
            text: parent.display
            color: "red"
            font.family: fontAwesomeSolid.name
            fontSizeMode: Text.Fit
            font.pointSize: 40
          }
        }

    }
}
