/* esQuickFontAwesomeLoader.qml ---
 *
 * Author: Julien Wintz
 * Created: Fri Dec  6 15:36:33 2013 (+0100)
 * Version:
 * Last-Updated:
 *           By:
 *     Update #: 27
 */

/* Change Log:
 *
 */

import QtQuick 2.1

FontLoader {
    source: "PluginStoreFontAwesome.ttf"
}

// /////////////////////////////////////////////////////////////////

/*

 \qmltype FontAwesomeLoader
 \inqmlmodule esQuick
 \ingroup Fonts
 \inherits FontAwesomeLoader
 \brief Loads esQuick's awesome font that provides glyphs to be
 convenienlty used as icons.

 \qml
 // somewhere in main.qml

 FontAwesomeLoader { id: awesome; }

 // anywhere

 FontAwesome {
     ...
 }
 \endqml

 \sa FontAwesome

*/
