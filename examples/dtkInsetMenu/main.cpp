/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Jun  2 13:56:26 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Jun  2 13:56:54 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 2
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
