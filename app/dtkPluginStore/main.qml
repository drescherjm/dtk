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
import QtQuick.Layouts 1.0

ApplicationWindow {

    visible: true;

    title: "dtkPluginStore";

    width: 640;
    height: 420;

    minimumHeight: 400;
    minimumWidth: 600;

    Rectangle { id: first;

        anchors.top: parent.top;
        anchors.left: parent.left;
        anchors.right: parent.right;
        height: 40;

        PluginStoreShaderEffect {
            gradient_top: "#666666";
            gradient_mid: "#555555";
            gradient_bot: "#222222";
        }
    }

    Rectangle { id: second;

        anchors.top: first.bottom;
        anchors.left: parent.left;
        anchors.right: parent.right;
        height: 40;

        PluginStoreShaderEffect {
            gradient_top: "#660000";
            gradient_mid: "#550000";
            gradient_bot: "#220000";
        }
    }

}




//
//main.qml ends here
