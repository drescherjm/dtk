/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Feb 12 21:01:33 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Sat Feb 13 21:32:16 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 59
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtCore>
#include <QtGui>

#include <dtkCore/dtkAbstractView.h>
#include <dtkCore/dtkAbstractViewFactory.h>
#include <dtkCore/dtkLog.h>
#include <dtkCore/dtkPluginManager.h>

#include <dtkVr/dtkVrMaster.h>
#include <dtkVr/dtkVrSlave.cpp>

#include <mpi.h>

int main(int argc, char **argv)
{
    QApplication application(argc, argv);

    dtkPluginManager::instance()->initialize();

    MPI::Init(argc, argv);

    int rank = MPI::COMM_WORLD.Get_rank();
    int size = MPI::COMM_WORLD.Get_size();

    dtkVrProcess *process = NULL;

    if (rank) {

        process = new dtkVrSlave;
        
        dtkAbstractView *view = dtkAbstractViewFactory::instance()->create("vtkViewVr");
        
        if (view) {
            view->widget()->show();
            view->widget()->resize(500, 320);
            view->widget()->move(rank-1 == 3 ? 500 : (rank-1)*500, rank-1 == 3 ? 350 : 0);
        } else {
            dtkWarning() << "Unable to get vtkViewVr view";
            return 1;
        }

        dynamic_cast<dtkVrSlave *>(process)->setView(view);

    } else {

        process = new dtkVrMaster;

    }

    qDebug() << "Running process" << rank << "of" << size;

    process->start(); // Qt's event loop is called from within dtkVrProcess' one.

    MPI::Finalize();

    dtkPluginManager::instance()->uninitialize();

    return 0;
}
