/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Feb 12 21:01:33 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Jul  9 10:44:55 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 145
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtCore>
#include <QtGui>
#include <QtOpenGL>

#include <dtkCore/dtkPluginManager.h>

#include <dtkVr/dtkVrManager.h>
#include <dtkVr/dtkVrMaster.h>
#include <dtkVr/dtkVrSlave.cpp>

int main(int argc, char **argv)
{
    if (argc < 3) {
        qDebug() << "Usage: dtkVrProcess --view <type> [--tracker <url>] [--device <url>] [--fullscreen] [--stereo]";
        return 1;
    }

    QApplication application(argc, argv);

    if(application.arguments().contains("--stereo")) {
       QGLFormat format;
       format.setAlpha(true);
       format.setDoubleBuffer(true);
       format.setStereo(true);
       format.setDirectRendering(true);
       QGLFormat::setDefaultFormat(format);
    }

    QUrl trackerUrl, deviceUrl;
    
    for(int i = 0; i < qApp->arguments().count(); i++) if(qApp->arguments().at(i) == "--tracker") trackerUrl = QUrl(qApp->arguments().at(i+1));
    for(int i = 0; i < qApp->arguments().count(); i++) if(qApp->arguments().at(i) == "--device")  deviceUrl  = QUrl(qApp->arguments().at(i+1));

    dtkPluginManager::instance()->initialize();
    
    dtkVrManager::instance()->setTracker(trackerUrl);
    dtkVrManager::instance()->setDevice(deviceUrl);
    dtkVrManager::instance()->setStereo(application.arguments().contains("--stereo"));

    dtkVrManager::instance()->initialize();

    dtkVrProcess *process = dtkVrManager::instance()->create(argv[2]);
    process->show(application.arguments().contains("--fullscreen"));
    process->start();

    dtkVrManager::instance()->uninitialize();

    dtkPluginManager::instance()->uninitialize();

    return 0;
}
