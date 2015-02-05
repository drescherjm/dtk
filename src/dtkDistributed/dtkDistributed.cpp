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

#include "dtkDistributed.h"
#include "dtkDistributedAbstractApplication.h"
#include "dtkDistributedApplication.h"
#include "dtkDistributedCoreApplication.h"
#include "dtkDistributedCommunicator.h"
#include "dtkDistributedPolicy.h"

namespace dtkDistributed
{
    namespace _private {
        dtkDistributed::Mode mode = dtkDistributed::Global;
        dtkDistributedAbstractApplication *app = NULL;
    }

    void setMode(dtkDistributed::Mode mode) {
        _private::mode = mode;
    }

    dtkDistributed::Mode mode(void) {
        return _private::mode;
    }

    dtkDistributedAbstractApplication* create(int &argc, char *argv[])
    {
        for (int i = 0; i < argc; i++)
            if(!qstrcmp(argv[i], "-nw") ||!qstrcmp(argv[i], "--nw") ||  !qstrcmp(argv[i], "-no-window")|| !qstrcmp(argv[i], "--no-window") || !qstrcmp(argv[i], "-h") || !qstrcmp(argv[i], "--help")|| !qstrcmp(argv[i], "--version")) {
                _private::app = new dtkDistributedCoreApplication(argc, argv);
                return _private::app;
            }
        _private::app = new dtkDistributedApplication(argc, argv);
        return _private::app;
    }

    dtkDistributedAbstractApplication *app(void) {
        if (!_private::app ) {
            _private::app = dynamic_cast<dtkDistributedAbstractApplication *>(dtkDistributedCoreApplication::instance());
            qDebug()<< _private::app;
        }
        return _private::app;
    }

    dtkDistributedPolicy *policy(void) {
        if (!app())
            return NULL;

        return _private::app->policy();
    }

    namespace communicator
    {
        namespace _private {
            dtkDistributedCommunicatorPluginFactory factory;
            dtkDistributedCommunicatorPluginManager manager;
        }

        dtkDistributedCommunicatorPluginFactory& pluginFactory(void) {
            return _private::factory;
        }

        dtkDistributedCommunicatorPluginManager& pluginManager(void) {
            return _private::manager;
        }
    }
}
