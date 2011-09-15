/* slave_main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Sep 14 13:19:42 2011 (+0200)
 * Version: $Id$
 * Last-Updated: jeu. sept. 15 11:43:18 2011 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 50
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtCore>

#include <dtkConfig.h>

#include <dtkCore/dtkPluginManager.h>
#include <dtkCore/dtkGlobal.h>

#include "dtkDistributedTutorial4Slave.h"

int main(int argc, char **argv)
{
    QCoreApplication application(argc, argv);

    if(argc < 2) {
        qDebug() << "Usage:" << argv[0] << "count";
        return 0;
    }

    const int max = 100000;

    int count = atoi(argv[1]);

    if(count > max) {
        qDebug() << "Count is too large";
        return 0;
    }

    QUrl url;
    if (dtkApplicationArgumentsContain(qApp,"--server"))
        url=QUrl(dtkApplicationArgumentsValue(qApp,"--server"));
    else
        return 0;

    qDebug() << "slave connecting to server " << url;

    dtkPluginManager::instance()->initialize();

    dtkDistributedTutorial4Slave *slave = new dtkDistributedTutorial4Slave;
    slave->connect(url);
    qDebug() << "slave connected to server " << slave->isConnected();

    slave->setCount(count);

    int status = slave->exec();

    dtkPluginManager::instance()->uninitialize();

    return status;
}
