/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Sep  5 13:19:19 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Sep  5 14:11:48 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 11
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

#include "tstMainWindow.h"

int main(int argc, char **argv)
{
    QApplication application(argc, argv);

    dtkPluginManager::instance()->initialize();
   
    tstMainWindow *window = new tstMainWindow;
    window->resize(400, 800);
    window->show();
    window->raise();

    int status =  application.exec();

    dtkPluginManager::instance()->uninitialize();

    return status;
}
