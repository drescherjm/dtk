/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Feb 12 21:01:33 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Feb 21 18:11:06 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 121
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtCore>
#include <QtGui>

#include <dtkCore/dtkPluginManager.h>

#include <dtkVr/dtkVrManager.h>
#include <dtkVr/dtkVrMaster.h>
#include <dtkVr/dtkVrSlave.cpp>

int main(int argc, char **argv)
{
    if (argc < 3) {
        qDebug() << "Usage: dtkVrProcess --view <type> [--tracker <url>]";
        return 1;
    }

    QApplication application(argc, argv);

    dtkPluginManager::instance()->initialize();
    dtkVrManager::instance()->initialize();

    dtkVrProcess *process = dtkVrManager::instance()->create(argv[2]);
    process->show();
    process->start();

    dtkVrManager::instance()->uninitialize();
    dtkPluginManager::instance()->uninitialize();

    return 0;
}
