//Version: $Id$
//
//

//Commentary:
//
//

//Change Log:
//
//

//Code:

import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

ButtonStyle {
    background: Rectangle {
        implicitWidth: 100
        implicitHeight: 24
        border.width: control.activeFocus ? 2 : 1
        border.color: "#888000"
        radius: 12
        gradient: Gradient {
            GradientStop { position: 0 ; color: control.pressed ? "#ccc000" : "#eee000" }
            GradientStop { position: 1 ; color: control.pressed ? "#aaa000" : "#ccc000" }
        }
    }
}

//
//PluginStoreButtonStyle.qml ends here
