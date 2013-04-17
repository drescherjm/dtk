/* dtk3DQuickViewTest.qml ---
 * 
 * Author: Julien Wintz
 * Created: Mon Apr  1 23:20:48 2013 (+0200)
 * Version: 
 * Last-Updated: Wed Apr 17 11:35:11 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 5
 */

/* Change Log:
 * 
 */

import    QtQuick 2.0
import dtk3DQuick 1.0

Quick3DView {
      
  width: 800;
  height: 500;
  
  Quick3DScene {
    
    id: scene;
    
    items: [
      Quick3DPoint { id: item1; x: +0.0; color: "red"; },
      Quick3DPoint { id: item2; x: +2.0; color: "green"; },
      Quick3DPoint { id: item3; x: -2.0; color: "blue"; }
    ]
  }
}
