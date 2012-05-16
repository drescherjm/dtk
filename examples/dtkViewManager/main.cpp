/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed May 16 09:42:04 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed May 16 09:48:36 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 7
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtGui>

#include "tstMainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    tstMainWindow w;
    w.resize(800, 600);
    w.show();
    w.raise();
    
    return a.exec();
}
