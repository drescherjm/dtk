/* dtkComposer.h ---
 * 
 * Author: Thibaud Kloczko
 * Created: Tue Apr  9 12:43:49 2013 (+0200)
 * Version: 
 * Last-Updated: Mon Apr 15 10:30:06 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 32
 */

/* Change Log:
 * 
 */

#pragma once

#include "dtkComposerExport.h"
#include <QtCore>

class dtkComposerNodeFactory;
class dtkComposerExtensionPlugin;
class dtkComposerExtensionPluginManager;
class dtkComposerExtensionPluginFactory;

namespace dtkComposer
{
    namespace node {
        DTKCOMPOSER_EXPORT dtkComposerNodeFactory *factory(void);
    }
    namespace extension {
        DTKCOMPOSER_EXPORT dtkComposerExtensionPluginFactory& pluginFactory(void);
        DTKCOMPOSER_EXPORT dtkComposerExtensionPluginManager& pluginManager(void);
        DTKCOMPOSER_EXPORT void initialize(const QString& path = "");
    }
}
