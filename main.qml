import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.12
import drawingTarget 1.0
import QtGraphicalEffects 1.0
import QtQuick.Controls.Material 2.12

ApplicationWindow {
    id:applicatonWnd
    visible: true
    title: qsTr("Application")
    width: 600
    height: 360
    Material.theme: Material.Light
    Material.background: Material.color(Material.BlueGrey)
    Column{
        spacing: 5
        leftPadding: 5
        rightPadding: 5
        Row{
            spacing: 5
            Button
            {
                id:btnFtype
                text: renderTarget.getFtype()
                font.bold: true
                Material.background: Material.Orange
                onClicked:
                {
                    renderTarget.setFtype(0);
                    btnFtype.text=renderTarget.getFtype()
                }
            }
            Button
            {
                text: "left"
                font.bold: true
                Material.background: Material.Orange
                onClicked: renderTarget.setDelta(10,-10);

            }
            Button
            {
                text: "Cls"
                font.bold: true
                Material.background: Material.Pink
                onClicked: renderTarget.cleareAllCharts()

            }
        }
        Row{
            MouseArea{
                id:area
                width: applicatonWnd.width-10-verticalSld.width
                height: applicatonWnd.height-150
                antialiasing: true
                hoverEnabled: true
                onClicked:
                {

                    // Вызывем функцию класса по нажатию кнопки
                    renderTarget.onMouseClick(area.mouseX,area.mouseY)
                }
                onPositionChanged:
                {
                    renderTarget.onMouseMove(area.mouseX,area.mouseY)
                    lblMousePos.text=renderTarget.getMousePos()
                }


                Rectangle
                {
                    id:backHolst
                    anchors.fill: area
                    state: "NORMAL"
                    radius:4
                    gradient: Gradient {
                              GradientStop { position: 0.0; color: Material.color(Material.Pink) }
                              GradientStop { position: 1.0; color: Material.color(Material.DeepPurple) }
                              //GradientStop { position: 0.0; color: Qt.rgba(246, 248 , 253, 1) }
                              //GradientStop { position: 1.0; color: Qt.rgba(199, 213, 237, 1) }

                          }
                }
                Target
                {
                    id:renderTarget
                    anchors.fill: parent
                    layer.enabled: true
                    layer.effect: DropShadow {
                        transparentBorder: true
                        horizontalOffset: 4
                        verticalOffset: 3
                    }

                }
            }
            Slider{
                id:verticalSld

                orientation: Qt.Vertical
                height: area.height
                from: -100
                to: 100
                value: 0
                onMoved:
                    renderTarget.setDelta(horisontallSld.value,verticalSld.value);
            }
        }
        Row
        {
            Slider{
                id:horisontallSld
                orientation: Qt.Horizontal
                width: area.width
                from: -100
                to: 100
                value: 0
                onMoved:
                    renderTarget.setDelta(horisontallSld.value,verticalSld.value);
            }
        }

        Row{
            Label
            {
                id:lblMousePos
                text: "pos"
                width: 100
                height: 20
                horizontalAlignment:  "AlignHCenter"
                background:
                    Rectangle{
                    anchors.fill:parent
                    radius: 5
                    color: Material.color(Material.Orange)
                }
            }
        }
    }
}


