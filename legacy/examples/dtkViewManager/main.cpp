/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed May 16 09:42:04 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Tue May 22 00:20:14 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 19
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtGui>

#include "tstMainWindow.h"

#include <dtkCore/dtkAbstractViewFactory.h>
#include <dtkCore/dtkPluginManager.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    dtkPluginManager::instance()->initialize();

    for(int i = 0; i < 4; i++)
        dtkAbstractViewFactory::instance()->create("oglViewVr");

    tstMainWindow w;
    w.resize(800, 600);
    w.show();
    w.raise();

    int status = a.exec();

    dtkPluginManager::instance()->uninitialize();

    return status;
}
