import QtQuick 2.12
import QtQuick.Controls 2.12

Item {
    id: networkSettings

    Rectangle{
        width: 270
        height: 20
        y: 80
        anchors.horizontalCenter: parent.horizontalCenter
        color: "transparent"

        Text {
            text: "Mode: "
            anchors.left: parent.left
            font.family: "Helvetica"
            font.pointSize: 16
            font.bold: true
            color: "black"
        }

        TabBar {
            id: tabBar
            anchors.right: parent.right
            background: Rectangle {
                color: "transparent"
                //radius: 10
            }

            TabButton {
                height: 30
                width: 60
                text: "DHCP"

                background: Rectangle {
                    color: tabBar.currentIndex == 0 ? "blue" : "black"
                    //radius: 10
                }
            }
            TabButton {
                height: 30
                width: 60
                text: "STATIC"
                background: Rectangle {
                    color: tabBar.currentIndex == 1 ? "blue" : "black"
                    //radius: 10
                }
            }
        }
    }


    Rectangle{
        width: 270
        height: 20
        y: 120
        anchors.horizontalCenter: parent.horizontalCenter
        color: "transparent"

        Text {
            text: "Connection: "
            anchors.left: parent.left
            font.family: "Helvetica"
            font.pointSize: 16
            font.bold: true
            color: "black"
        }

        TabBar {
            id: connectionTab
            anchors.right: parent.right
            background: Rectangle {
                color: "transparent"
                //radius: 10
            }

            TabButton {
                height: 30
                width: 60
                text: "Wired"

                background: Rectangle {
                    color: connectionTab.currentIndex == 0 ? "blue" : "black"
                    //radius: 10
                }
            }
            TabButton {
                height: 30
                width: 60
                text: "Wifi"
                background: Rectangle {
                    color: connectionTab.currentIndex == 1 ? "blue" : "black"
                    //radius: 10
                }
            }
        }
    }



    Rectangle{
        width: 270
        height: 20
        y: 180
        anchors.horizontalCenter: parent.horizontalCenter
        color: "transparent"

        Text {
            text: "IP address: "
            anchors.left: parent.left
            font.family: "Helvetica"
            font.pointSize: 16
            font.bold: true
            color: "black"
        }


        TextField {
            id: control
            anchors.right: parent.right
            placeholderText: qsTr("192.168.137.63")
            color: "black"
            font.bold: true

            background: Rectangle {
                implicitWidth: 140
                implicitHeight: 30
                color: control.enabled ? "transparent" : "#353637"
                border.color: control.enabled ? "#21be2b" : "transparent"
            }

        }

    }

    Rectangle{
        width: 270
        height: 20
        y: 240
        anchors.horizontalCenter: parent.horizontalCenter
        color: "transparent"

        Text {
            text: "Mask: "
            anchors.left: parent.left
            font.family: "Helvetica"
            font.pointSize: 16
            font.bold: true
            color: "black"
        }


        TextField {
            id: mask
            anchors.right: parent.right
            placeholderText: qsTr("255.255.255.0")
            color: "black"
            font.bold: true

            background: Rectangle {
                implicitWidth: 140
                implicitHeight: 30
                color: mask.enabled ? "transparent" : "#353637"
                border.color: mask.enabled ? "#21be2b" : "transparent"
            }

        }

    }

    Rectangle{
        width: 270
        height: 20
        y: 300
        anchors.horizontalCenter: parent.horizontalCenter
        color: "transparent"

        Text {
            text: "Gateway: "
            anchors.left: parent.left
            font.family: "Helvetica"
            font.pointSize: 16
            font.bold: true
            color: "black"
        }


        TextField {
            id: gateway
            anchors.right: parent.right
            placeholderText: qsTr("192.168.137.1")
            color: "black"
            font.bold: true

            background: Rectangle {
                implicitWidth: 140
                implicitHeight: 30
                color: gateway.enabled ? "transparent" : "#353637"
                border.color: gateway.enabled ? "#21be2b" : "transparent"
            }

        }

    }

}
