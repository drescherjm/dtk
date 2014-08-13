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

Rectangle {

    id: toolbar;

    // /////////////////////////////////////////////////////////////////

    property bool cloud: true;

    // /////////////////////////////////////////////////////////////////

    color: "#dddddd";


    // /////////////////////////////////////////////////////////////////

    PluginStoreSeparator { id: sep_1; anchors.top: toolbar.top; direction: Qt.Horizontal; color: "#cccccc"; }

    MouseArea {
        anchors.top: parent.top;
        anchors.left: parent.left;
        anchors.bottom: parent.bottom;

        width: toolbar.width/2;

        PluginStoreFontAwesome {
            anchors.centerIn: parent;
            size: 25;
            icon: PluginStoreFontAwesomeIcon.Icon.Cloud;
            color: cloud ? "#555555" : "#888888";
        }

        onClicked: {
            if(!cloud)
                 cloud = true;
        }
    }

    MouseArea {
        anchors.top: parent.top;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;

        width: toolbar.width/2;

        PluginStoreFontAwesome {
            anchors.centerIn: parent;
            size: 25;
            icon: PluginStoreFontAwesomeIcon.Icon.Drive;
            color: cloud ? "#888888" : "#555555";
        }

        onClicked: {
            if (cloud)
                cloud = false;
        }
    }
}


//
//dtkPluginStoreToolBar.qml ends here
