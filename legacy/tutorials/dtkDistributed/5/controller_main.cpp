/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Sep 20 11:21:15 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Sep 20 12:50:27 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 15
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "tstMainWindow.h"

#include <QtCore>
#include <QtGui>
#include <QtDebug>

int main(int argc, char **argv)
{
    QApplication application(argc, argv);

    tstMainWindow *window = new tstMainWindow;
    window->raise();
    window->show();
    window->resize(600, 300);

    return application.exec();
}
