 /* dtk3DQuickShortcuts.qml ---
 * 
 * Author: Julien Wintz
 * Created: Wed Apr 10 16:55:14 2013 (+0200)
 * Version: 
 * Last-Updated: Fri Apr 12 17:31:45 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 312
 */

/* Change Log:
 * 
 */

import QtQuick 2.0

Image {

  property Item view;

  id: dtk3DQuickShortcuts;
  source: "dtk3DQuickShortcutsBackground.png";
  fillMode: Image.Tile;

  ListModel {

    id: dtk3DQuickShortcutsModel;

    ListElement { name: "Toggle pick buffer painting"; category: "Painting"; key: "Tab"; modifier: "No"; }

    ListElement { name: "Fit";            category: "Camera shortcuts"; key: "F"; modifier: "No";  }
    ListElement { name: "Fit -X aligned"; category: "Camera shortcuts"; key: "X"; modifier: "Alt"; }
    ListElement { name: "Fit +X aligned"; category: "Camera shortcuts"; key: "X"; modifier: "No";  }
    ListElement { name: "Fit -Y aligned"; category: "Camera shortcuts"; key: "Y"; modifier: "Alt"; }
    ListElement { name: "Fit +Y aligned"; category: "Camera shortcuts"; key: "Y"; modifier: "No";  }
    ListElement { name: "Fit -Z aligned"; category: "Camera shortcuts"; key: "Z"; modifier: "Alt"; }
    ListElement { name: "Fit +Z aligned"; category: "Camera shortcuts"; key: "Z"; modifier: "No";  }

    ListElement { name: "Fit";            category: "Item shortcuts"; key: "F"; modifier: "No";  }
    ListElement { name: "Fit -X aligned"; category: "Item shortcuts"; key: "X"; modifier: "Alt"; }
    ListElement { name: "Fit +X aligned"; category: "Item shortcuts"; key: "X"; modifier: "No";  }
    ListElement { name: "Fit -Y aligned"; category: "Item shortcuts"; key: "Y"; modifier: "Alt"; }
    ListElement { name: "Fit +Y aligned"; category: "Item shortcuts"; key: "Y"; modifier: "No";  }
    ListElement { name: "Fit -Z aligned"; category: "Item shortcuts"; key: "Z"; modifier: "Alt"; }
    ListElement { name: "Fit +Z aligned"; category: "Item shortcuts"; key: "Z"; modifier: "No";  }
  }

  ListView {

    id: dtk3DQuickShortcutsView;
    model: dtk3DQuickShortcutsModel;
    delegate: dtk3DQuickShortcutsDelegate;

    anchors.fill: parent;

    section.property: "category";
    section.criteria: ViewSection.FullString;
    section.delegate: dtk3DQuickShortcutsSectionDelegate;
    section.labelPositioning: ViewSection.InlineLabels | ViewSection.CurrentLabelAtStart;
  }
  
  // ///////////////////////////////////////////////////////////////////
  // dtk3DQuickShortcutsDelegate
  // ///////////////////////////////////////////////////////////////////

  Component {

    id: dtk3DQuickShortcutsDelegate;
    
    Rectangle {

      width: dtk3DQuickShortcuts.width;
      height: 64;
      color: "#272727";
        
      Text {
        text: name; 
        color: "#dddddd";
        font.family: "Menlo";
        font.pixelSize: 12;
        anchors.left: parent.left;
        anchors.leftMargin: 10;
        anchors.verticalCenter: parent.verticalCenter;
      }

      Image {
        id: dtk3DQuickShortcutsModifier;
        source: "dtk3DQuickShortcuts" + modifier + "Modifier.png";
        width: parent.height;
        height: parent.height;
        anchors.right: dtk3DQuickShortcutsKey.left;
      }
      
      Image {
        id: dtk3DQuickShortcutsKey;
        source: "dtk3DQuickShortcutsKey" + key + ".png";
        width: parent.height;
        height: parent.height;
        anchors.right: parent.right;
      }

      Rectangle { x: 0; y: parent.height - 2; width: dtk3DQuickShortcuts.width; height: 1; color: "#151515"; }
      Rectangle { x: 0; y: parent.height - 1; width: dtk3DQuickShortcuts.width; height: 1; color: "#363636"; }

      // MouseArea {
      //   anchors.fill: parent;
      //   onPressed: {
      //     trigger(dtk3DQuickShortcutsModel.get(index));
      //   } 
      // }
    }
  }

  // ///////////////////////////////////////////////////////////////////
  // dtk3DQuickShortcutsSectionDelegate
  // ///////////////////////////////////////////////////////////////////

  Component {

    id: dtk3DQuickShortcutsSectionDelegate;

    Rectangle {

      width: dtk3DQuickShortcuts.width;
      height: 30;

      gradient: Gradient {
        GradientStop { position: 0.0; color: "#3c3c3c"; }
        GradientStop { position: 1.0; color: "#303030"; }
      }

      Text {
        text: section;
        color: "#000000";
        x: dtk3DQuickShortcutsSectionDelegateText.x-1;
        y: dtk3DQuickShortcutsSectionDelegateText.y-1;
        font.family: "Courier";
        font.pixelSize: 14;
      }

      Text {
        id: dtk3DQuickShortcutsSectionDelegateText;
        text: section;
        color: "#666666";
        anchors.centerIn: parent;
        font.family: "Courier";
        font.pixelSize: 14;
      }

      Rectangle { x: 0; y: 0;                 width: dtk3DQuickShortcuts.width; height: 1; color: "#575757"; }
      Rectangle { x: 0; y: parent.height - 2; width: dtk3DQuickShortcuts.width; height: 1; color: "#151515"; }
      Rectangle { x: 0; y: parent.height - 1; width: dtk3DQuickShortcuts.width; height: 1; color: "#363636"; }
    }
  }

  // ///////////////////////////////////////////////////////////////////
  // Helper fuunctions
  // ///////////////////////////////////////////////////////////////////

  function trigger(shortcut) {

      if(shortcut.category == "Painting") {

          if(shortcut.key == "Tab")
              view.togglePickPainting();
      }
    
      if(shortcut.category == "Camera shortcuts") {
          
          if(shortcut.key == "F")
              view.fit();

          if(shortcut.key == "X" && shortcut.modifier == "No")
              view.fitFromRight();
          
          if(shortcut.key == "X" && shortcut.modifier == "Alt")
              view.fitFromLeft();

          if(shortcut.key == "Y" && shortcut.modifier == "No")
              view.fitFromTop();

          if(shortcut.key == "Y" && shortcut.modifier == "Alt")
              view.fitFromBottom();

          if(shortcut.key == "Z" && shortcut.modifier == "No")
              view.fitFromFront();

          if(shortcut.key == "Z" && shortcut.modifier == "Alt")
              view.fitFromBack();
      }

      if(shortcut.category == "Item shortcuts") {

          console.log("Item interaction is not yet supported");
      }
  }
}
