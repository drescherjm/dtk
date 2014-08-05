/* esQuickFontAwesome.qml ---
 *
 * Author: Julien Wintz
 * Created: Fri Dec  6 15:38:19 2013 (+0100)
 * Version:
 * Last-Updated:
 *           By:
 *     Update #: 82
 */

/* Change Log:
 *
 */

import QtQuick 2.1

Text {
    id: self;

    property alias icon: self.text;
    property alias size: self.font.pixelSize;

    font.family: root.font_iconic.name;
}

// /////////////////////////////////////////////////////////////////

/*

 \qmltype FontAwesome
 \ingroup Fonts
 \inherits Text

 \brief

 Instantiates esQuick's awesome font item as a glyph icon.

 \qml
 FontAwesome {
     size: 25;
     icon: FontAwesome.Icon.Glass;
 }
 \endqml

 \qmlproperty text FontAwesome::icon
   The unicode identifier of an awesome icon. Use the associated
   script to reference it, e.g. Awesome.Icon.Glass.

 \qmlproperty real FontAwesome::size
   The size of the icon, device pixel independant (expressed in
   points).

 \sa FontAwesomeLoader

*/
