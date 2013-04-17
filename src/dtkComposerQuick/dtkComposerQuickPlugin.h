/* dtkComposerQuickPlugin.h ---
 * 
 * Author: Julien Wintz
 * Created: Wed Apr 17 10:31:51 2013 (+0200)
 * Version: 
 * Last-Updated: Wed Apr 17 10:32:16 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 2
 */

/* Change Log:
 * 
 */

#pragma once

#include <QQmlExtensionPlugin>

class dtkComposerQuickPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char *uri);
};
