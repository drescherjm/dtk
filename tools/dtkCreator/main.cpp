/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Aug  3 17:37:15 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Apr 24 23:39:39 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 75
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkLog/dtkLog.h>

#include <dtkCore/dtkPluginManager.h>

#include "dtkCreatorMainWindow.h"

#include <QtGui>

int main(int argc, char **argv)
{
    QApplication application(argc, argv);
    application.setApplicationName("dtkCreator");
    application.setOrganizationName("inria");
    application.setOrganizationDomain("fr");
    application.setApplicationVersion("0.9.9");

    QSettings settings("inria", "dtk");
    settings.beginGroup("creator");

    if (settings.contains("log_level"))
        dtkLogger::instance().setLevel(settings.value("log_level").toString());
    else
        dtkLogger::instance().setLevel(dtkLog::Trace);

    dtkLogger::instance().attachFile(dtkLogPath(&application));

    dtkPluginManager::instance()->initialize();

    dtkCreatorMainWindow mainwindow;
    mainwindow.show();
    mainwindow.raise();

    int status = application.exec();

    dtkPluginManager::instance()->uninitialize();

    return status;
}
