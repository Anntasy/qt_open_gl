/* This file is generated and only relevant for integrating the project into a Qt 6 and cmake based
C++ project. */


import QtQuick
import content
// import QtQuick.Window
import my_opengl

App {
    visible: true
        width: 800; height: 600
        color: "#202225"

        FBO {
            id: gl
            anchors.fill: parent
            q_angle: 45
            focus: true
        }
}
