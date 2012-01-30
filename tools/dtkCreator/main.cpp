/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Aug  3 17:37:15 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Jan 30 19:43:43 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 60
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkCore/dtkPluginManager.h>

#include "dtkCreatorMainWindow.h"

#include <QtGui>

int main(int argc, char **argv)
{
    QApplication application(argc, argv);
    application.setApplicationName("dtkCreator");
    application.setOrganizationName("inria");
    application.setOrganizationDomain("fr");
    application.setApplicationVersion("0.1.0");

    dtkPluginManager::instance()->initialize();

    dtkCreatorMainWindow mainwindow;
    mainwindow.show();
    mainwindow.raise();

    int status = application.exec();

    dtkPluginManager::instance()->uninitialize();

    return status;
}
