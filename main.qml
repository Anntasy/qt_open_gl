/* This file is generated and only relevant for integrating the project into a Qt 6 and cmake based
C++ project. */


import QtQuick
import content
// import QtQuick.Window
import my_opengl

App {
    visible: true
        width: 1000; height: 1000
        color: "#202225"

        FBO {
            id: gl
            width: 1000; height: 1000
            anchors.fill: parent
            focus: true
            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.LeftButton
                onPressed: (mouse)=> {
                    parent.mousePressEvent(mouse.x, mouse.y, mouse.buttons);
                           }

                onPositionChanged: (mouse)=> {
                    parent.mouseMoveEvent(mouse.x, mouse.y, mouse.buttons);
                }

                hoverEnabled: true

                onReleased: (mouse)=> {
                    parent.mouseReleaseEvent(mouse.x, mouse.y, mouse.buttons);
                }
            }

        }
}
