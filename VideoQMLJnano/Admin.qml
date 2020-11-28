import QtQuick 2.12
import QtQuick.Controls 2.12
import com.ulasdikme.admin 1.0

Item {
    id: adminMain
    width: 800 //parent.width
    height: 480 //parent.height

    Rectangle{

        width: 400
        height: 300
        y:30
        color: "transparent"
        anchors.horizontalCenter: parent.horizontalCenter

            Text {
                text: "Name: "
                id: textName
                anchors.left: parent.left
                font.family: "Helvetica"
                font.pointSize: 24
                font.bold: true
                color: "black"
            }

            TextField {
                id: control
                anchors.right:  parent.right
                placeholderText: "Gina Atkins"
                color: "black"
                font.pointSize: 18
                font.bold: true

                background: Rectangle {
                    implicitWidth: 240
                    implicitHeight: 40
                    color: control.enabled ? "transparent" : "#353637"
                    border.color: control.enabled ? "#21be2b" : "transparent"
                }

            }

            Text {
                text: "Phone: "
                id: phoneText
                y: 60
                anchors.left: parent.left
                font.family: "Helvetica"
                font.pointSize: 24
                font.bold: true
                color: "black"
            }

            TextField {
                id: phone
                y: 60
                anchors.right:  parent.right
                placeholderText: "555 256 54 23"
                color: "black"
                font.pointSize: 18
                font.bold: true

                background: Rectangle {
                    implicitWidth: 240
                    implicitHeight: 40
                    color: phone.enabled ? "transparent" : "#353637"
                    border.color: phone.enabled ? "#21be2b" : "transparent"
                }

            }

            Text {
                text: "Email: "
                id: emailText
                y: 120
                anchors.left: parent.left
                font.family: "Helvetica"
                font.pointSize: 24
                font.bold: true
                color: "black"
            }

            TextField {
                id: email
                y: 120
                anchors.right:  parent.right
                placeholderText: "gina@gmail.com"
                color: "black"
                font.pointSize: 18
                font.bold: true

                background: Rectangle {
                    implicitWidth: 240
                    implicitHeight: 40
                    color: email.enabled ? "transparent" : "#353637"
                    border.color: email.enabled ? "#21be2b" : "transparent"
                }

            }

            Button {

                text: "Update"
                //anchors.top : parent.bottom
               // anchors.left: control.right;
                //anchors.margins: 10
                y : 170
                anchors.right: parent.right
                //anchors.topMargin: 40
                //anchors.horizontalCenter: parent.horizontalCenter
                background: Rectangle {
                    implicitWidth: 90
                    implicitHeight: 30
                    border.width: email.activeFocus ? 2 : 1
                    border.color: "#888"
                    radius: 4
                    gradient: Gradient {
                        GradientStop { position: 0 ; color: hotspotButton.pressed ? "#ccc" : "#eee" }
                        GradientStop { position: 1 ; color: hotspotButton.pressed ? "#aaa" : "#ccc" }
                    }
                }
                objectName: "hotspotButton"
                signal hotspotButton()
                id:hotspotButton
                onClicked:
                {

                }
            }

    }


}
