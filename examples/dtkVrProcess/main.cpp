/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Feb 12 21:01:33 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon May  9 14:57:16 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 153
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
        qDebug() << "Usage: dtkVrProcess --view <type> [--fullscreen] [--stereo]";
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

    dtkPluginManager::instance()->initialize();    
    dtkVrManager::instance()->setStereo(application.arguments().contains("--stereo"));
    dtkVrManager::instance()->initialize();

    dtkVrProcess *process = dtkVrManager::instance()->create(argv[2]);
    process->show(application.arguments().contains("--fullscreen"));
    process->start();

    delete process;

    dtkVrManager::instance()->uninitialize();
    dtkPluginManager::instance()->uninitialize();

    return 0;
}
