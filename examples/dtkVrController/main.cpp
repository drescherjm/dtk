/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Jan 25 12:23:54 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Jan 25 12:23:58 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 2
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtGui/QApplication>

#include "tstMainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    tstMainWindow w; w.show();

    return a.exec();
}
