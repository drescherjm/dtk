/* dtkDistributed.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Mon Mar 25 09:23:52 2013 (+0100)
 * Version: 
 * Last-Updated: Tue Apr  9 12:28:59 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 3
 */

/* Change Log:
 * 
 */

#include "qthDistributedCommunicator.h"

#include "dtkDistributed.h"
#include "dtkDistributedApplication.h"
#include "dtkDistributedCommunicator.h"
#include "dtkDistributedPolicy.h"
#include "dtkDistributedSettings.h"

namespace dtkDistributed
{
    namespace _private {
        dtkDistributed::Mode mode = dtkDistributed::Global;
        dtkDistributedApplication *app = NULL;
    }

    void setMode(dtkDistributed::Mode mode) {
        _private::mode = mode;
    }

    dtkDistributed::Mode mode(void) {
        return _private::mode;
    }

    dtkDistributedApplication* create(int &argc, char *argv[])
    {
        for (int i = 0; i < argc; i++)
            if(!qstrcmp(argv[i], "-nw") ||!qstrcmp(argv[i], "--nw") ||  !qstrcmp(argv[i], "-no-window")|| !qstrcmp(argv[i], "--no-window") || !qstrcmp(argv[i], "-h") || !qstrcmp(argv[i], "--help")|| !qstrcmp(argv[i], "--version")) {
                qputenv("QT_QPA_PLATFORM", QByteArrayLiteral("minimal"));
            }
        _private::app = new dtkDistributedApplication(argc, argv);
        return _private::app;
    }

    dtkDistributedApplication *app(void) {
        if (!_private::app ) {
            _private::app = dynamic_cast<dtkDistributedApplication *>(qApp);
        }
        return _private::app;
    }

    dtkDistributedPolicy *policy(void) {
        if (!app())
            return NULL;

        return _private::app->policy();
    }

    void spawn(void) {
        if (!app())
            return;

        _private::app->spawn();
    }

    void exec(QRunnable *task) {
        if (!app())
            return;

        _private::app->exec(task);
    }

    void unspawn(void) {
        if (!app())
            return;

        _private::app->unspawn();
    }

    namespace communicator
    {
        namespace _private {
            dtkDistributedCommunicatorPluginFactory factory;
            dtkDistributedCommunicatorPluginManager manager;
            dtkDistributedCommunicator *communicator = NULL;
        }

        dtkDistributedCommunicatorPluginFactory& pluginFactory(void) {
            return _private::factory;
        }

        dtkDistributedCommunicatorPluginManager& pluginManager(void) {
            return _private::manager;
        }
        void initialize(const QString& path) {
            pluginFactory().record("qthread", qthDistributedCommunicatorCreator);
            pluginManager().initialize(path);
        }

        dtkDistributedCommunicator *instance(void) {
            dtkDistributedApplication *app = dtkDistributed::app();
            if (_private::communicator) {
                return _private::communicator;
            } else if (app) {
                _private::communicator = app->communicator();
            } else {
                dtkDistributedSettings settings;
                settings.beginGroup("communicator");
                pluginManager().initialize(settings.value("plugins").toString());
                _private::communicator = dtkDistributed::communicator::pluginFactory().create("qthread");
            }
            return _private::communicator;
        }
    }
}
