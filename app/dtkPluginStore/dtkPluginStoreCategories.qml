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

import "PluginStoreFontAwesome.js" as PluginStoreFontAwesomeIcon

Item { id: wrapper;

    signal clicked;

    anchors.fill: parent;

    Rectangle {

        id: header;

        anchors.fill: parent;

        PluginStoreShaderEffect {
            gradient_top: "#666666";
            gradient_mid: "#555555";
            gradient_bot: "#333333";
        }

        MouseArea {
            anchors.right: parent.right;
            anchors.top: parent.top;
            width: 40;
            height: 40;
            onClicked: {
                wrapper.clicked();
            }

            PluginStoreFontAwesome {
                anchors.centerIn: parent;
                size: 25;
                icon: PluginStoreFontAwesomeIcon.Icon.Search;
                color: "#888888";
            }
        }
    }

    PluginStoreSeparator { id: sep_1; anchors.top: header.bottom; direction: Qt.Horizontal; color: "#555555"; }
    PluginStoreSeparator { id: sep_2; anchors.top: sep_1.bottom; direction: Qt.Horizontal; color: "#000000"; }
}

//
//PluginStoreCategories.qml ends here
