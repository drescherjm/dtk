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
#include "dtkComposerFactoryManager.h"
#include "dtkComposerExtension.h"
#include "dtkComposerSettings.h"

namespace dtkComposer
{
    namespace node
    {
        namespace _private {
            dtkComposerFactoryManager manager;
        }
        dtkComposerNodeFactory *factory(void) {
            return _private::manager.factory();
        }
        void initialize(void) {
            _private::manager.initNodeBase();
            _private::manager.initNodeBoolean();
            _private::manager.initNodeControl();
            _private::manager.initNodeConstants();
            _private::manager.initNodeDistributed();
            _private::manager.initNodeFile();
            _private::manager.initNodeNumber();
            _private::manager.initNodeString();
            _private::manager.initNodeContainer();
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
            QString realpath = path;

            if (realpath.isEmpty()) {
                dtkComposerSettings composer_settings;
                composer_settings.beginGroup("extension");
                realpath = composer_settings.value("plugins").toString();
                composer_settings.endGroup();
                if (realpath.isEmpty()) {

                    realpath = QDir(DTK_INSTALL_PREFIX).filePath("plugins/dtkComposer");
                    dtkDebug() << "no composer plugin path configured, use default:" << realpath ;
                }
                pluginManager().setVerboseLoading(true);
                pluginManager().initialize(realpath);
            } else {
                dtkDebug() << "initialize composer plugins using path:" << path ;
                pluginManager().initialize(path);
            }
        }
    }
}
