/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sat Jun 12 15:52:11 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Sat Jun 12 15:52:31 2010 (+0200)
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
    QApplication application(argc, argv);
    application.setApplicationName("dtkFinder");
    application.setOrganizationName("inria");

    tstMainWindow window;
    window.show();

    return application.exec();
}
