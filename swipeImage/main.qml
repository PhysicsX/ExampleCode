import QtQuick 2.15
import QtQuick.Controls 2.3

ApplicationWindow {
   visible: true
   width: 900
   height: 900
   title: qsTr("Image Slider")
   SwipeView{
      id:slider

      height: parent.height/1.7
      width: height
      //x:(parent.width-width)/2//make item horizontally center
      property var model :ListModel{}
      clip:true
      Repeater {

          model:slider.model
          Rectangle {

              width: slider.width
              height: slider.height
              x:200
              y:200
              color: "yellow"

              Rectangle
              {
                  width: slider.width  / 5
                  height: slider.height / 5
                  color: "gray"
                  opacity: 0.4
                  z:99
              }

              Text {
                  width: 10
                  height: 10
                  id: name
                  text: textUpdate
                  font.family: "Helvetica"
                  font.pointSize: 28
                  font.bold: true
                  color: "black"
                  z:99
              }

              Image{
                 width: slider.width
                 height: slider.height
                 source:image
                 fillMode: Image.Stretch
              }

          }

      }
   }
//   PageIndicator {
//      anchors.top: slider.bottom
//      anchors.topMargin: verticalMargin
//      x:(parent.width-width)/2
//      currentIndex: slider.currentIndex
//      count: slider.count
//   }
Component.onCompleted: {

 slider.model.append
 (
     {textUpdate:"ulas", image:"http://www.shropshiresgreatoutdoors.co.uk/wp-content/uploads/2015/08/Prices-Dingle-400x400.jpg"}
 )
 slider.model.append({textUpdate:"john", image:"http://1.bp.blogspot.com/-6PYPT11obnA/Tlc9KFGj1HI/AAAAAAAAFUc/5I_IeithKZ8/s400/Latest-Nature.jpg"})
 slider.model.append({textUpdate:"linda", image:"http://www.shropshiresgreatoutdoors.co.uk/wp-content/uploads/2015/08/Prices-Dingle-400x400.jpg"})
 slider.model.append({textUpdate:"anna", image:"http://1.bp.blogspot.com/-6PYPT11obnA/Tlc9KFGj1HI/AAAAAAAAFUc/5I_IeithKZ8/s400/Latest-Nature.jpg"})

}
}
