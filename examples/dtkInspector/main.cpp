/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Mar 23 21:02:12 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Mar 24 12:56:17 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 5
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
    window->show();
    window->resize(800, 480);

    return application.exec();
}
