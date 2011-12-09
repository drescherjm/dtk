/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Aug  3 17:37:15 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Nov 17 10:17:15 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 52
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtGui/QApplication>
#include <QtOpenGL/QGLFormat>

#include <dtkCore/dtkPluginManager.h>

#include <dtkScript/dtkScriptManager.h>

#include "dtkCreatorMainWindow.h"

int main(int argc, char **argv)
{
    QApplication application(argc, argv);
    application.setApplicationName("dtkCreator");
    application.setOrganizationName("inria");
    application.setOrganizationDomain("fr");
    application.setApplicationVersion("0.1.0");

    dtkPluginManager::instance()->initialize();
    dtkScriptManager::instance()->initialize();

    if(application.arguments().contains("--stereo")) {
       QGLFormat format;
       format.setAlpha(true);
       format.setDoubleBuffer(true);
       format.setStereo(true);
       format.setDirectRendering(true);
       QGLFormat::setDefaultFormat(format);
    }

    dtkCreatorMainWindow mainwindow; mainwindow.show();

    if(application.arguments().contains("--script"))
        mainwindow.interpret(application.arguments().value(application.arguments().indexOf("--script")+1));

    int status = application.exec();

    dtkPluginManager::instance()->uninitialize();
    dtkScriptManager::instance()->uninitialize();

    return status;
}
