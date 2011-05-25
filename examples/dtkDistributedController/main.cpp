/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed May 25 16:02:43 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Wed May 25 16:15:34 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 14
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtCore>
#include <QtGui>
#include <QtDebug>

#include "tstMainWindow.h"

int main(int argc, char **argv)
{
    QApplication application(argc, argv);

    tstMainWindow *window = new tstMainWindow;
    window->resize(640, 400);
    window->show();
    window->raise();

    return application.exec();
}
