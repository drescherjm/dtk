/* dtk3DQuickViewTest.qml ---
 * 
 * Author: Julien Wintz
 * Created: Mon Apr  1 23:20:48 2013 (+0200)
 * Version: 
 * Last-Updated: Wed Apr  3 10:59:26 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 111
 */

/* Change Log:
 * 
 */

import    QtQuick 2.0
import dtk3DQuick 1.0


Rectangle {
    
    id: root;

    width: 1024;
    height: 512;

    color: "#ff0000";

    Quick3DView {
        
        anchors.fill: parent;
        anchors.margins: 50;
    } 
}
