/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Aug  3 17:37:15 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Sat Nov 14 14:20:02 2009 (+0100)
 *           By: Julien Wintz
 *     Update #: 40
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

#ifdef Q_WS_MAC
#include <dtkGui/dtkCocoaController.h>
#endif

#include "dtkCreatorMainWindow.h"

int main(int argc, char **argv)
{
#ifdef Q_WS_MAC
    dtkCocoaController::instance()->initialize();
#endif

    QApplication application(argc, argv);
    application.setApplicationName("dtkCreator");
    application.setOrganizationName("inria");
    application.setOrganizationDomain("fr");
    application.setApplicationVersion("0.1.0");

    dtkPluginManager::instance()->initialize();
    dtkScriptManager::instance()->initialize();

    dtkCreatorMainWindow mainwindow; mainwindow.show();

    if(application.arguments().contains("--script"))
        mainwindow.interpret(application.arguments().value(application.arguments().indexOf("--script")+1));

    // if(application.arguments().contains("--stereo")) {
        QGLFormat format; format.setStereo(true);
        QGLFormat::setDefaultFormat(format);
    // }

    int status = application.exec();

    // dtkPluginManager::instance()->uninitialize();
    dtkScriptManager::instance()->uninitialize();

#ifdef Q_WS_MAC
    dtkCocoaController::instance()->uninitialize();
#endif

    return status;
}
