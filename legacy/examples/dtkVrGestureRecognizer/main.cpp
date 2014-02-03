/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Oct 21 19:19:53 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Oct 21 19:20:01 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 1
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtCore>
#include <QtGui>

#include "tstMainWindow.h"

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    QUrl tracker;

    for(int i = 0; i < qApp->arguments().count(); i++) if(qApp->arguments().at(i) == "--tracker") tracker = QUrl(qApp->arguments().at(i+1));

    tstMainWindow window;
    window.setTracker(tracker);
    window.show();

    return application.exec();
}
