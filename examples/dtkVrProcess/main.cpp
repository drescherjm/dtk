/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Feb 12 21:01:33 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Sat Feb 20 11:52:34 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 108
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
    QApplication application(argc, argv);

    dtkPluginManager::instance()->initialize();
    
    dtkVrManager::instance()->initialize();

    dtkVrProcess *process = dtkVrManager::instance()->create("vtkViewVr");
    process->initialize();
    process->show();
    process->start();
    process->uninitialize();

    dtkVrManager::instance()->uninitialize();

    dtkPluginManager::instance()->uninitialize();

    return 0;
}
