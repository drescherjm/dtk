/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Feb 12 21:01:33 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 22 09:05:02 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 123
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
        qDebug() << "Usage: dtkVrProcess --view <type> [--tracker <url>] [--fullscreen]";
        return 1;
    }

    QApplication application(argc, argv);

    dtkPluginManager::instance()->initialize();
    dtkVrManager::instance()->initialize();

    dtkVrProcess *process = dtkVrManager::instance()->create(argv[2]);
    process->show(application.arguments().contains("--fullscreen"));
    process->start();

    dtkVrManager::instance()->uninitialize();
    dtkPluginManager::instance()->uninitialize();

    return 0;
}
