/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Feb 12 21:01:33 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Feb 18 08:52:23 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 95
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtCore>
#include <QtGui>

#include <dtkVr/dtkVrMaster.h>
#include <dtkVr/dtkVrSlave.cpp>

int main(int argc, char **argv)
{
    QApplication application(argc, argv);

    dtkVrController::instance()->initialize();

    dtkVrProcess *process = dtkVrController::instance()->createProcess("vtkViewVr");

    process->initialize();

    if (process->rank()) {
        process->view()->widget()->show();
        process->view()->widget()->resize(500, 320);
        process->view()->widget()->move(
            process->rank()-1 == 3 ? 500 : (process->rank()-1)*500,
            process->rank()-1 == 3 ? 350 : 0);
    }

    process->start();
    process->uninitialize();

    dtkVrController::instance()->uninitialize();

    return 0;
}
