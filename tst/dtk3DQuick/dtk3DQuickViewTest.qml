/* dtk3DQuickViewTest.qml ---
 * 
 * Author: Julien Wintz
 * Created: Mon Apr  1 23:20:48 2013 (+0200)
 * Version: 
 * Last-Updated: Thu Apr  4 11:30:48 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 181
 */

/* Change Log:
 * 
 */

import    QtQuick 2.0
import dtk3DQuick 1.0

Quick3DView {
        
    id: view;

    width: 1024;
    height: 512;

    Quick3DScene {

        id: scene;

        items: [
            Quick3DItem { id: item1; color: "red"; },
            Quick3DItem { id: item2; color: "green"; x: -2.0; },
            Quick3DItem { id: item3; color: "blue";  x: +2.0; }
        ]
    }
} 
