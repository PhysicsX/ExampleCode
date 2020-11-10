import QtQuick 2.12
import QtQuick.Controls 2.12
import com.ulasdikme.networkManager 1.0

Item {
    id: networkSettings
    signal example()
    objectName: "networkSettings"
    Component.onCompleted: {

        console.log("Network loaded");
        console.log(networkManager.enableDHCP);
        tabBar.currentIndex = networkManager.enableDHCP;

    }
    Rectangle{
        width: 470
        height: 50
        y: 50
        anchors.horizontalCenter: parent.horizontalCenter
        color: "transparent"

        Text {
            text: "Mode: "
            anchors.left: parent.left
            font.family: "Helvetica"
            font.pointSize: 24
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
                height: 50
                width: 120
                text: "DHCP"
                font.pointSize: 16

                background: Rectangle {
                    id: tabRect
                    color: tabBar.currentIndex == 0 ? "blue" : "black"
                    //radius: 10
                }
            }
            TabButton {
                height: 50
                width: 120
                text: "STATIC"
                font.pointSize: 16

                background: Rectangle {
                    id: tabRect2
                    color: tabBar.currentIndex == 1 ? "blue" : "black"
                    //radius: 10
                }
            }
        }
    }


    Rectangle{
        width: 470
        height: 50
        y: 120
        anchors.horizontalCenter: parent.horizontalCenter
        color: "transparent"

        Text {
            text: "Connection: "
            anchors.left: parent.left
            font.family: "Helvetica"
            font.pointSize: 24
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
                height: 50
                width: 120
                text: "Wired"
                font.pointSize: 16

                background: Rectangle {
                    color: connectionTab.currentIndex == 0 ? "blue" : "black"
                    //radius: 10
                }
            }
            TabButton {
                height: 50
                width: 120
                text: "Wifi"
                font.pointSize: 16

                background: Rectangle {
                    color: connectionTab.currentIndex == 1 ? "blue" : "black"
                    //radius: 10
                }
            }
        }
    }



    Rectangle{
        width: 470
        height: 50
        y: 180
        anchors.horizontalCenter: parent.horizontalCenter
        color: "transparent"

        Text {
            text: "IP address: "
            anchors.left: parent.left
            font.family: "Helvetica"
            font.pointSize: 24
            font.bold: true
            color: "black"
        }


        TextField {
            id: control
            anchors.right: parent.right
            text: networkManager.ipAddr
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

    }

    Rectangle{
        width: 470
        height: 50
        y: 240
        anchors.horizontalCenter: parent.horizontalCenter
        color: "transparent"

        Text {
            text: "Mask: "
            anchors.left: parent.left
            font.family: "Helvetica"
            font.pointSize: 24
            font.bold: true
            color: "black"
        }


        TextField {
            id: mask
            anchors.right: parent.right
            text: networkManager.maskAddr //qsTr("255.255.255.0")
            color: "black"
            font.pointSize: 18
            font.bold: true

            background: Rectangle {
                implicitWidth: 240
                implicitHeight: 40
                color: mask.enabled ? "transparent" : "#353637"
                border.color: mask.enabled ? "#21be2b" : "transparent"
            }

        }

    }

    Rectangle{
        width: 470
        height: 50
        y: 300
        anchors.horizontalCenter: parent.horizontalCenter
        color: "transparent"

        Text {
            text: "Gateway: "
            anchors.left: parent.left
            font.family: "Helvetica"
            font.pointSize: 24
            font.bold: true
            color: "black"
        }


        TextField {
            id: gateway
            anchors.right: parent.right
            text: networkManager.routerAddr //qsTr("192.168.137.1")
            color: "black"
            font.pointSize: 18
            font.bold: true

            background: Rectangle {
                implicitWidth: 240
                implicitHeight: 40
                color: gateway.enabled ? "transparent" : "#353637"
                border.color: gateway.enabled ? "#21be2b" : "transparent"
            }

        }

    }

    Rectangle{
        width: 270
        height: 50
        y: 355
        //anchors.horizontalCenter: parent.horizontalCenter
        anchors.right: parent.right
        color: "transparent"


        Button {
            text: "Apply"
           // id:controlButton

            background: Rectangle {
                implicitWidth: 100
                implicitHeight: 25
                border.width: control.activeFocus ? 2 : 1
                border.color: "#888"
                radius: 4
                gradient: Gradient {
                    GradientStop { position: 0 ; color: controlButton.pressed ? "#ccc" : "#eee" }
                    GradientStop { position: 1 ; color: controlButton.pressed ? "#aaa" : "#ccc" }
                }
            }
            objectName: "controlButton"
            signal qmlSignalForIpChange()
            id:controlButton

            NetworkManager{
                id: networkManager
                //ipAddr: ipAddr
                onIpAddrChanged:{
                    control.text = ipAddr;
                    console.log("ipaddr is updated");
                }

                onMaskAddrChanged:{
                    mask.text = maskAddr;
                    console.log("maskAddr is updated");
                }

                onRouterAddrChanged:{
                    gateway.text = routerAddr;
                    console.log("routerAddr is updated");
                }

                onEnableDHCPChanged:{
                    tabBar.currentIndex = enableDHCP;
                     console.log("enableDHCP is updated");
                }

            }

            onClicked:
            {
                //controlButton.qmlSignalForIpChange()
                console.log("Apply is clicked");
                console.log("tabbar "+tabBar.currentIndex);
                console.log("connectionTab "+connectionTab.currentIndex);
                if(tabBar.currentIndex === 0)
                {
                    networkManager.applyNetwork(tabBar.currentIndex, connectionTab.currentIndex);
                    networkManager.enableDHCP = 0;
                }
                else if(tabBar.currentIndex === 1)
                {
                    console.log("static configuration");
                    networkManager.ipAddr = control.text;
                    networkManager.maskAddr = mask.text;
                    networkManager.routerAddr = gateway.text;
                    networkManager.setStatic();
                    networkManager.enableDHCP = 1;
                }

            }
        }
    }

}
