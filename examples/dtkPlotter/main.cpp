/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Feb 17 12:52:28 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Feb 17 12:53:35 2011 (+0100)
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

#include "dtkPlotterMainWindow.h"

int main(int argc, char **argv)
{
    QApplication application(argc, argv);

    dtkPlotterMainWindow *window = new dtkPlotterMainWindow;
    window->show();

    int status = application.exec();

    delete window;;

    return status;
}
