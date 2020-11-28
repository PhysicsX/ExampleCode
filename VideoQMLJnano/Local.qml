import QtQuick 2.0
import QtQuick.Controls 2.12
import com.ulasdikme.local 1.0

Item {

    id: localMain
    width: 800 //parent.width
    height: 480 //parent.height

    Rectangle{

        width: 400
        height: 300
        y:30
        color: "transparent"
        anchors.horizontalCenter: parent.horizontalCenter

        Text {
            text: "Temp: "
            id: textName
            anchors.left: parent.left
            font.family: "Helvetica"
            font.pointSize: 24
            font.bold: true
            color: "black"
        }

        ComboBox{
            width: 200
            anchors.right:  parent.right
            model: ["Fahrenheit", "Celcius"]
        }

        Text {
            text: "Distance: "
            id: distance
            y: 60
            anchors.left: parent.left
            font.family: "Helvetica"
            font.pointSize: 24
            font.bold: true
            color: "black"
        }

        ComboBox{
            width: 200
            y: 60
            anchors.right:  parent.right
            model: ["Feet", "Meter"]
        }

        Text {
            text: "Time: "
            id: time
            y: 120
            anchors.left: parent.left
            font.family: "Helvetica"
            font.pointSize: 24
            font.bold: true
            color: "black"
        }

        TextField {
            id: timeText
            y: 120
            anchors.right:  parent.right
            placeholderText: "12:22:00"
            color: "black"
            font.pointSize: 18
            font.bold: true

            background: Rectangle {
                implicitWidth: 240
                implicitHeight: 40
                color: timeText.enabled ? "transparent" : "#353637"
                border.color: timeText.enabled ? "#21be2b" : "transparent"
            }

        }

        Text {
            text: "Date: "
            id: date
            y: 180
            anchors.left: parent.left
            font.family: "Helvetica"
            font.pointSize: 24
            font.bold: true
            color: "black"
        }

        TextField {
            id: dateText
            y: 180
            anchors.right:  parent.right
            placeholderText: "Oct-12-20"
            color: "black"
            font.pointSize: 18
            font.bold: true

            background: Rectangle {
                implicitWidth: 240
                implicitHeight: 40
                color: dateText.enabled ? "transparent" : "#353637"
                border.color: dateText.enabled ? "#21be2b" : "transparent"
            }

        }

        Text {
            text: "Zone: "
            id: zone
            y: 240
            anchors.left: parent.left
            font.family: "Helvetica"
            font.pointSize: 24
            font.bold: true
            color: "black"
        }

        TextField {
            id: zoneText
            y: 240
            anchors.right:  parent.right
            placeholderText: "Pacific"
            color: "black"
            font.pointSize: 18
            font.bold: true

            background: Rectangle {
                implicitWidth: 240
                implicitHeight: 40
                color: zoneText.enabled ? "transparent" : "#353637"
                border.color: zoneText.enabled ? "#21be2b" : "transparent"
            }

        }

    }
}
