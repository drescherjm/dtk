/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Aug  3 17:37:15 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Aug  4 16:01:16 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 20
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtGui/QApplication>

#include <dtkCore/dtkPluginManager.h>

#include "dtkCreatorMainWindow.h"

int main(int argc, char **argv)
{
    QApplication application(argc, argv);
    application.setApplicationName("dtkCreator");
    application.setOrganizationName("inria");
    application.setOrganizationDomain("fr");
    application.setApplicationVersion("0.1.0");

    dtkPluginManager::instance()->initialize();

    dtkCreatorMainWindow *mainwindow = new dtkCreatorMainWindow; mainwindow->show();
    
    int status = application.exec();

    dtkPluginManager::instance()->uninitialize();

    return status;
}
