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

        id: search;

        anchors.fill: parent;

        PluginStoreShaderEffect {
            gradient_top: "#cccccc";
            gradient_mid: "#bbbbbb";
            gradient_bot: "#999999";
        }

        Rectangle {

            anchors.fill: parent;
            anchors.margins: 10;
            anchors.rightMargin: 50;

            color: "#ffffff";
            radius: 10;

            border.color: "#8f8f8f";

            TextInput {
                anchors.fill: parent;
                anchors.leftMargin: 10;
            }
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
                color: "#666666";
            }
        }
    }

    PluginStoreSeparator { id: sep_3; anchors.top: search.bottom; direction: Qt.Horizontal; color: "#bbbbbb"; }
    PluginStoreSeparator { id: sep_4; anchors.top: sep_3.bottom; direction: Qt.Horizontal; color: "#888888"; }

}

//
//PluginStoreSearch.qml ends here
