/* dtk3DQuickPlugin.h ---
 * 
 * Author: Julien Wintz
 * Created: Mon Apr  1 21:47:10 2013 (+0200)
 * Version: 
 * Last-Updated: Mon Apr  1 21:48:36 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 5
 */

/* Change Log:
 * 
 */

#pragma once

#include <QQmlExtensionPlugin>

class dtk3DQuickPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char *uri);
};
