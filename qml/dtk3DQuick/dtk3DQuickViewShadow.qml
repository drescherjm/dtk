/* dtk3DQuickViewShadow.qml ---
 * 
 * Author: Julien Wintz
 * Created: Thu Apr 11 10:00:09 2013 (+0200)
 * Version: 
 * Last-Updated: Thu Apr 11 10:16:14 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 6
 */

/* Change Log:
 * 
 */

import QtQuick 2.0

BorderImage {

  property Item view;

  anchors.fill: view;
  anchors {
       topMargin: -8;
      leftMargin: -8;
     rightMargin: -8;
    bottomMargin: -8;
  }
  border {
       top: 10;
      left: 10;
     right: 10;
    bottom: 10;
  }
  source: "dtk3DQuickViewShadow.png";
  smooth: true;
}
