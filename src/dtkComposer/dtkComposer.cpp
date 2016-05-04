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
#include "dtkComposerExtension.h"
#include "dtkComposerSettings.h"
#include "dtkComposerDefaultExtensions.h"

namespace dtkComposer
{
    namespace node
    {
        namespace _private {
            dtkComposerNodeFactory factory;
        }
        dtkComposerNodeFactory& factory(void) {
            return _private::factory;
        }
        void initialize(void) {
            dtkComposerBaseExtension baseExt;
            baseExt.extend(&(_private::factory));
            dtkComposerBooleanExtension boolExt;
            boolExt.extend(&(_private::factory));
            dtkComposerControlExtension controlExt;
            controlExt.extend(&(_private::factory));
            dtkComposerConstantsExtension constantsExt;
            constantsExt.extend(&(_private::factory));
            dtkComposerDistributedExtension distributedExt;
            distributedExt.extend(&(_private::factory));
            dtkComposerFileExtension fileExt;
            fileExt.extend(&(_private::factory));
            dtkComposerNumberExtension numberExt;
            numberExt.extend(&(_private::factory));
            dtkComposerStringExtension stringExt;
            stringExt.extend(&(_private::factory));
            dtkComposerContainerExtension containerExt;
            containerExt.extend(&(_private::factory));
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
