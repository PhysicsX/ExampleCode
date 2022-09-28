import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.0
import Painter 1.0

Window {
    width: Screen.width
    height: Screen.height
    visible: true
    title: qsTr("OpencvToQml")


        QmlType {
	    objectName: "inputCamera"
            id: inputView
            //streamerThreadSlot: VideoStreamer
            width: parent.width
            height: parent.height


        }

}
