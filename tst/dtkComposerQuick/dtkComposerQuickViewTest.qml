/* dtkComposerQuickViewTest.qml ---
 * 
 * Author: Julien Wintz
 * Created: Wed Apr 17 10:58:53 2013 (+0200)
 * Version: 
 * Last-Updated: Fri Apr 19 17:16:10 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 35
 */

/* Change Log:
 * 
 */

import          QtQuick 2.0
import dtkComposerQuick 1.0

// QuickComposerView {

Item {

  id: view;

  QuickComposerGraph { id: graph; }
  QuickComposerStack { id: stack; }
  QuickComposerScene {

    graph: graph;
    stack: stack;

    anchors.fill: parent;

    nodes: [
      QuickComposerNode { type: "boolean"; },
      QuickComposerNode { type: "boolean"; },
      QuickComposerNode { type: "boolean"; },
      QuickComposerNode { type: "and"; }
    ]
  }
}
