/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Sep 20 11:21:15 2011 (+0200)
 * Version: $Id$
 * Last-Updated: mar. déc.  6 17:32:34 2011 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 18
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "tstMainWindow.h"

#include <dtkCore/dtkPluginManager.h>
#include <QtCore>
#include <QtGui>
#include <QtDebug>

int main(int argc, char **argv)
{
    QApplication application(argc, argv);


    dtkPluginManager::instance()->initialize();

    tstMainWindow *window = new tstMainWindow;
    window->raise();
    window->show();
    window->resize(600, 300);

    return application.exec();
}
