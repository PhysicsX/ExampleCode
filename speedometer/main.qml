import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.VirtualKeyboard 2.4
import QtQuick.Extras 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 1.4

Window {
    id: window
    visible: true
    width: 1000
    height: 1000

    title: qsTr("Back camera")

    Rectangle
    {
        id: dashboard
        height: 500
        width: 1000
        color: "black";
        CircularGauge{
            id:speedometer
            value: acceleration ? maximumValue : 0
            anchors.centerIn: parent
            width: parent.width * 0.5
            height: parent.height * 0.8
            maximumValue: 180

            property bool acceleration: false

            Keys.onUpPressed: {

                acceleration = true
            }

            Keys.onReleased: {
                if(event.key === Qt.Key_Up)
                {
                    acceleration = false;
                    event.accepted = true;
                }
            }

           style: CircularGaugeStyle{
                background: Canvas {
                        Row {
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.top: parent.verticalCenter
                            anchors.topMargin: outerRadius * - 0.3

                            Text {
                                id : speedText
                                color: "white"
                                font.pixelSize: outerRadius * 0.1
                                horizontalAlignment: Text.AlignRight
                                text:kphValue
                                readonly property int  kphValue: speedometer.value

                            }
                            Text {
                                id: unitSpeed
                                text: " Km/h"
                                color: "white"
                                font.pixelSize: outerRadius * 0.1

                            }
                        }
                    }
                }


            Behavior on value{
                NumberAnimation{
                    duration: 9000
                }
            }
            Component.onCompleted: forceActiveFocus();

        }
    }



}
