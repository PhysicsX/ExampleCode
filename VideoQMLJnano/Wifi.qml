import QtQuick 2.12
import QtQuick.Window 2.2
import QtQuick.Controls 2.12
import com.ulasdikme.wifiConf 1.0

Item {
    property bool flagToUpt: false;
    width: parent.width
    height: parent.height
    visible: true

    Component.onCompleted: {

        console.log("wifiqml is loaded");
        console.log(wifiConf.enableHot)
        if(!wifiConf.enableHot)
        {
            station.visible = true;
            hotspot.visible = false;
        }
        else
        {
            station.visible = false;
            hotspot.visible = true;
        }
        console.log(wifiConf.ssidNames.length)
        console.log(wifiConf.ssidNames[2])

        model.clear();
        for(var i = 0; i < wifiConf.ssidNames.length; i++)
        {
            model.append({name: wifiConf.ssidNames[i], number: "strong" });
        }
//        model.append({name: "ssid1", number: "strong"});
//        model.append({name: "ssid2", number: "strong"});
//        model.append({name: "ssid3", number: "normal"});
//        model.append({name: "ssid4", number: "weak"});
//        model.append({name: "ssid5", number: "weak"});
    }

    WifiConf{
    id: wifiConf
        onSsidNamesChanged:
        {
            console.log("ssids updated");
            model.clear();
            for(var i = 0; i < wifiConf.ssidNames.length; i++)
            {
                model.append({name: wifiConf.ssidNames[i], number: "strong" });
            }
        }
    }

    ListModel {
        id: model
        ListElement {
            name:'ssid1'
            number:'strong'
        }
    }

    Rectangle
    {
        width: 400
        height: 300
        color:"transparent"
        //anchors.top: parent.top
        y : 15
        anchors.horizontalCenter: parent.horizontalCenter
        Text {

            color: "green"
            font.pixelSize: 28
            font.weight: Font.DemiBold
            text: wifiConf.enableHot ? 'Update ssid and password' : 'Double tap to connect'
         }
    }

    Rectangle
    {
        id: hotspot
        width: 400
        height: 180
        y: 80
        color: "transparent"
        anchors.horizontalCenter: parent.horizontalCenter

        TextField
        {
            id: hotspotSsid
            width: 220
            height: 30
            y: 20
            placeholderText: "Enter SSID"
            echoMode: TextInput.Normal
            anchors.horizontalCenter: parent.horizontalCenter

        }

        TextField
        {
            id: hotspotpass
            width: 220
            height: 30
            y: 60
            placeholderText: "Enter Password"
            echoMode: TextInput.Password
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {

            text: "Update"
            //anchors.top : parent.bottom
           // anchors.left: control.right;
            //anchors.margins: 10
            y : 100
            anchors.right: hotspotpass.right
            //anchors.topMargin: 40
            //anchors.horizontalCenter: parent.horizontalCenter
            background: Rectangle {
                implicitWidth: 90
                implicitHeight: 30
                border.width: hotspotpass.activeFocus ? 2 : 1
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
                console.log("hotspotButton network is clicked");
                wifiConf.updateHotspot(hotspotSsid.text, hotspotpass.text);
            }
        }

    }

    Rectangle
    {
        width: 400
        height: 180
        y: 80
        color: "transparent"
        id: station
        anchors.horizontalCenter: parent.horizontalCenter


        ListView {
            id: list
            anchors.fill: parent
            model: model

            delegate: Component {
                Item {
                    width: parent.width
                    height: 80
                    Column {
                        Text {
                            color: "blue"
                            font.pixelSize: 24
                            font.weight: Font.DemiBold
                            text: 'Name: ' + name }
                        Text {
                            color: "blue"
                            font.pixelSize: 24
                            font.weight: Font.DemiBold
                            text: 'Strength: ' + number }
                        TapHandler{
                            onDoubleTapped:
                            {
                                list.currentIndex = index
                                flagToUpt = true;
                                console.log(flagToUpt)
                                //rec2.color = "black";
                            }

                        }
                    }

                }
            }
            highlight: Rectangle {
                id: rec2
                color: flagToUpt ? 'black' : 'transparent'
                opacity: 0.3

                Text {
                    z : 90

                    //anchors.centerIn: parent
                    //anchors.bottom: parent.bottom
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.bottom: parent.bottom
                    text: 'Connect to ' + model.get(list.currentIndex).name
                    color: flagToUpt ? 'white' : 'transparent'
                    font.pixelSize: 18
                }
            }
            focus: true
            onCurrentItemChanged: console.log(model.get(list.currentIndex).name + ' selected')
        }

            TextField
            {
                id: control
                width: 160
                height: 30
                placeholderText: "Enter password"
                echoMode: TextInput.Password
                anchors.top : parent.bottom
                anchors.margins: 40
            }
            Button {

                text: "Connect"
                anchors.top : parent.bottom
                anchors.left: control.right;
                //anchors.margins: 10
                anchors.leftMargin: 30
                anchors.topMargin: 40
                //anchors.horizontalCenter: parent.horizontalCenter
                background: Rectangle {
                    implicitWidth: 90
                    implicitHeight: 30
                    border.width: control.activeFocus ? 2 : 1
                    border.color: "#888"
                    radius: 4
                    gradient: Gradient {
                        GradientStop { position: 0 ; color: connectButton.pressed ? "#ccc" : "#eee" }
                        GradientStop { position: 1 ; color: connectButton.pressed ? "#aaa" : "#ccc" }
                    }
                }
                objectName: "connectButton"
                signal connetButtonSıgnal()
                id:connectButton
                onClicked:
                {
                    console.log(control.text);
                    console.log(model.get(list.currentIndex).name);
                    console.log("connect network is clicked");
                    wifiConf.connectToNetwork(model.get(list.currentIndex).name, control.text);
                }
            }

            Button {
            text: "Rescan"
            anchors.top : parent.bottom
            anchors.margins: 20
            anchors.topMargin: 40
            anchors.right: parent.right
            background: Rectangle {
                implicitWidth: 90
                implicitHeight: 30
                border.width: control.activeFocus ? 2 : 1
                border.color: "#888"
                radius: 4
                gradient: Gradient {
                    GradientStop { position: 0 ; color: scanBtn.pressed ? "#ccc" : "#eee" }
                    GradientStop { position: 1 ; color: scanBtn.pressed ? "#aaa" : "#ccc" }
                }
            }
            objectName: "scanBtn"
            signal rescanButtonSıgnal()
            id:scanBtn
            onClicked:
            {
                console.log("scanBtn is clicked");
                wifiConf.reScan();
            }
            }
    }


}
