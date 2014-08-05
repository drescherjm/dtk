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

ApplicationWindow { id: root

    property FontLoader font_iconic: PluginStoreFontAwesomeLoader {}

    // /////////////////////////////////////////////////////////////////

    visible: true;

    title: "dtkPluginStore";

    width: 640;
    height: 420;

    minimumHeight: 400;
    minimumWidth: 600;

    PluginStoreFlipper { id: flipper;

        anchors.top: parent.top;
        anchors.left: parent.left;
        anchors.right: parent.right;
        height: 40;

        front: PluginStoreCategories { onClicked: flipper.swap(); }
        back: PluginStoreSearch { onClicked: flipper.swap(); }
    }
}

//
//main.qml ends here
