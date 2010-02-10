/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Feb  9 11:12:18 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Feb 10 14:03:32 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 19
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

    tstMainWindow *mainwindow = new tstMainWindow;
    mainwindow->show();

    int status = application.exec();

    dtkPluginManager::instance()->uninitialize();

    return status;
}
