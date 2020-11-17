import QtQuick 2.12
import QtQuick.Window 2.12
import QtMultimedia 5.12
import QtQuick.Controls 2.3

Window {
    visible: true
    width: 1024
    height: 768
    title: qsTr("Hello World")

    MediaPlayer {
        id: player // sudo apt install gstreamer1.0-libav -> to run mp4 videoOutput
        source :"gst-pipeline: filesrc location=/home/jnano/Desktop/video.mp4 ! qtdemux ! queue ! decodebin ! videoconvert ! qtvideosink"
        //source : "file:///home/jnano/Desktop/video.mp4"
        //source: "gst-pipeline: videotestsrc ! qtvideosink"
        //source: "gst-pipeline: playbin uri=https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_trailer-480p.webm"
        //source: "gst-pipeline: nvarguscamerasrc ! autovideoconvert ! qtvideosink"
        //source: "file:///home/jnano/Desktop/build-VideoOutput-Desktop-Release/file_example_WEBM_480_900KB.webm"
        //source: "file:///home/ulas/Desktop/file_example_WEBM_1920_3_7MB.webm"
        autoPlay: true

    }

    VideoOutput {
        id: videoOutput
        source: player
        anchors.fill: parent
    }


    Repeater {
        model: rectlist
        delegate: Rectangle{
            x: modelData.rect.x
            y: modelData.rect.y
            width: modelData.rect.width
            height: modelData.rect.height
            color: "transparent"
            border.color: "black"
            border.width: 3
            Text{
                anchors.centerIn: parent
                text: modelData.text
            }
        }
    }
}
