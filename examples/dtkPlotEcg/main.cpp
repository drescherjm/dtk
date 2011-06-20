/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jun  7 15:28:37 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Jun  8 10:02:05 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 7
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

int main(int argc, char **argv)
{
    QApplication application(argc, argv);

    tstMainWindow *window = new tstMainWindow;
    window->resize(900, 500);
    window->show();
    window->raise();

    return application.exec();
}
