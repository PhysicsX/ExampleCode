import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls 2.5

Item {

    id: adminMain
    width: 800 //parent.width
    height: 480 //parent.height

    Rectangle{

        width: 10
        height: 300
        y:30
        color: "transparent"
        //anchors.horizontalCenter: parent.horizontalCenter
        anchors.left: parent.left
        anchors.leftMargin: parent.width * 0.4

            CheckBox{
                checked: true
                text : qsTr("Activate Audio")
                anchors.left: parent.left
            }
            CheckBox{
                checked: true
                text : qsTr("Enable LED statu")
                y:50
                anchors.left: parent.left
            }
            CheckBox{
                checked: true
                text : qsTr("Enable Text Feature")
                y: 100
                anchors.left: parent.left
            }
            CheckBox{
                checked: true
                text : qsTr("Activate Email Alarm")
                y: 150
                anchors.left: parent.left
            }
    }

}
