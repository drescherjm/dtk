/* dtk3DQuickShortcuts.qml ---
 * 
 * Author: Julien Wintz
 * Created: Wed Apr 10 16:55:14 2013 (+0200)
 * Version: 
 * Last-Updated: Thu Apr 11 00:12:12 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 124
 */

/* Change Log:
 * 
 */

import QtQuick 2.0

Rectangle {

  id: dtk3DQuickShortcuts;
  color: "darkgray";

  ListModel {
    id: dtk3DQuickShortcutsModel;

    ListElement { name: "Fit";            size: "Camera shortcuts" }
    ListElement { name: "Fit -X aligned"; size: "Camera shortcuts" }
    ListElement { name: "Fit +X aligned"; size: "Camera shortcuts" }
    ListElement { name: "Fit -Y aligned"; size: "Camera shortcuts" }
    ListElement { name: "Fit +Y aligned"; size: "Camera shortcuts" }
    ListElement { name: "Fit -Z aligned"; size: "Camera shortcuts" }
    ListElement { name: "Fit +Z aligned"; size: "Camera shortcuts" }

    ListElement { name: "Fit";            size: "Item shortcuts" }
    ListElement { name: "Fit -X aligned"; size: "Item shortcuts" }
    ListElement { name: "Fit +X aligned"; size: "Item shortcuts" }
    ListElement { name: "Fit -Y aligned"; size: "Item shortcuts" }
    ListElement { name: "Fit +Y aligned"; size: "Item shortcuts" }
    ListElement { name: "Fit -Z aligned"; size: "Item shortcuts" }
    ListElement { name: "Fit +Z aligned"; size: "Item shortcuts" }
  }

  ListView {

    id: dtk3DQuickShortcutsView;
    model: dtk3DQuickShortcutsModel;
    delegate: dtk3DQuickShortcutsDelegate;

    anchors.fill: parent;

    section.property: "size";
    section.criteria: ViewSection.FullString;
    section.delegate: dtk3DQuickShortcutsSectionDelegate;
    section.labelPositioning: ViewSection.InlineLabels | ViewSection.CurrentLabelAtStart;
  }
  
  // ///////////////////////////////////////////////////////////////////
  // dtk3DQuickShortcutsDelegate
  // ///////////////////////////////////////////////////////////////////

  Component {
    id: dtk3DQuickShortcutsDelegate;

    Text {
      x: 5;
      text: name; 
      font.family: "Menlo";
      font.pixelSize: 12;
    }
  }

  // ///////////////////////////////////////////////////////////////////
  // dtk3DQuickShortcutsSectionDelegate
  // ///////////////////////////////////////////////////////////////////

  Component {

    id: dtk3DQuickShortcutsSectionDelegate;

    Rectangle {

      color: "dimgray";
      width: dtk3DQuickShortcuts.width;
      height: 20;

      Text {
        text: section;
        color: "white";
        verticalAlignment: Text.AlignVCenter;
        horizontalAlignment: Text.AlignHCenter;
        anchors.fill: parent;
        font.family: "Menlo";
        font.pixelSize: 14;
      }
    }
  }
}
