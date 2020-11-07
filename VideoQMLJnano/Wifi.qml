import QtQuick 2.12
import QtQuick.Window 2.2
import QtQuick.Controls 1.3


Item {
    property bool flagToUpt: false;
    width: parent.width
    height: parent.height
    visible: true

    ListModel {
        id: model
        ListElement {
            name:'ssid1'
            number:'strong'
        }
        ListElement {
            name:'ssid2'
            number:'normal'
        }
        ListElement {
            name:'ssid3'
            number:'weak'
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
            text: 'Double tap to connect'
         }
    }

    Rectangle
    {
        width: 400
        height: 300
        y: 80
        color: "transparent"
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
                            text: 'Number: ' + number }
                        TapHandler{
                            onDoubleTapped:
                            {
                                list.currentIndex = index
                                flagToUpt = true;
                                console.log(flagToUpt)
                            }

                        }
                    }

                }
            }
            highlight: Rectangle {
                color: flagToUpt ? 'black' : 'transparent'
                opacity: 0.3
                Text {
                    //anchors.centerIn: parent
                    //anchors.bottom: parent.bottom
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    text: 'Connect to ' + model.get(list.currentIndex).name
                    color: flagToUpt ? 'white' : 'transparent'
                    font.pixelSize: 18
                }
            }
            focus: true
            onCurrentItemChanged: console.log(model.get(list.currentIndex).name + ' selected')
        }
    }
}
