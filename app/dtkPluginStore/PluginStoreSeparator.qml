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

Rectangle {

    property var direction;
    property color col;

    width: (direction === Qt.Vertical) ? 1 : parent.width;
    height: (direction === Qt.Horizontal) ? 1 : parent.height;

    color: col;
}

//
//PluginStoreSeparator.qml ends here
