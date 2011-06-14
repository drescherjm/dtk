/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Feb  3 17:03:55 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Feb  3 21:46:22 2010 (+0100)
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

#include "dtkAssistantMainWindow.h"

#include <dtkHelp/dtkHelpController.h>

int main(int argc, char **argv)
{
    QApplication application(argc, argv);

    dtkHelpController::instance()->initialize();

    dtkAssistantMainWindow *window = new dtkAssistantMainWindow; window->show();

    int status = application.exec();

    delete window;

    dtkHelpController::instance()->uninitialize();
}
