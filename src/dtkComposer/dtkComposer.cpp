/* dtkComposer.cpp ---
 *
 * Author: Thibaud Kloczko
 * Created: Tue Apr  9 12:49:06 2013 (+0200)
 */

/* Change Log:
 *
 */

#include "dtkComposer.h"

#include <dtkConfig.h>

#include "dtkComposerNodeFactory.h"
#include "dtkComposerFactory.h"
#include "dtkComposerExtension.h"

namespace dtkComposer
{
    namespace node
    {
        dtkComposerNodeFactory *factory(void) {
            return dtkComposerFactory::instance();
        }
    }

    namespace extension
    {
        namespace _private {
            dtkComposerExtensionPluginFactory factory;
            dtkComposerExtensionPluginManager manager;
        }

        dtkComposerExtensionPluginFactory& pluginFactory(void) {
            return _private::factory;
        }

        dtkComposerExtensionPluginManager& pluginManager(void) {
            return _private::manager;
        }
        void initialize(const QString& path) {
            if (path.isEmpty()) {
                QString default_path = QDir(DTK_INSTALL_PREFIX).filePath("plugins/dtkComposer");
                dtkDebug() << "no composer plugin path configured, use default:" << default_path ;
                pluginManager().setVerboseLoading(true);
                pluginManager().initialize(default_path);
            } else {
                dtkDebug() << "initialize composer plugins using path:" << path ;
                pluginManager().initialize(path);
            }
        }
    }
}
