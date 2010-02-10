/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Feb  9 11:12:18 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Feb  9 11:31:45 2010 (+0100)
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

    tstMainWindow *mainwindow = new tstMainWindow;
    mainwindow->show();

    return application.exec();
}
