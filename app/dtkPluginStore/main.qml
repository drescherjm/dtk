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

import "PluginStoreFontAwesome.js" as PluginStoreFontAwesomeIcon

ApplicationWindow { id: root

    property FontLoader font_iconic: PluginStoreFontAwesomeLoader {}

    // /////////////////////////////////////////////////////////////////

    visible: true;

    title: "dtkPluginStore";

    width: 420;
    height: 640;

    minimumHeight: 600;
    minimumWidth: 400;

    PluginStoreFlipper { id: flipper;

        anchors.top: parent.top;
        anchors.left: parent.left;
        anchors.right: parent.right;
        height: 40;

        front: PluginStoreCategories {
            onClicked: flipper.flipUp();
        }
        back: PluginStoreSearch {
            onClicked: flipper.flipDown();
        }
    }

    ListModel {

        id: model;

        ListElement {
            name: "blas sparse matrix operators"
        }
        ListElement {
            name: "blaze sparse matrix operators"
        }
        ListElement {
            name: "eigen sparse matrix operators"
        }
        ListElement {
            name: "thread communicator"
        }
        ListElement {
            name: "mpi communicator"
        }
    }

    ListView {

        id: view;

        anchors.top: flipper.bottom;
        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;


            clip: true;
           model: model;
        delegate: Rectangle {
            id: delegate
            width: ListView.view.width
            height: 40;

            Text {
                anchors.left: parent.left
                anchors.topMargin: 30;
                anchors.leftMargin: 10;
                text: name;
                color: "#666"
                font.pixelSize: 24;
            }

            Rectangle {
                height: 1
                color: "#ccc"
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
            }
        }
    }

    PluginStoreToolBar {

        id: toolbar;

        anchors.left: parent.left;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;

        height: 40;
    }
}

//
//main.qml ends here
