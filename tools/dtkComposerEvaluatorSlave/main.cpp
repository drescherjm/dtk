/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Oct 27 14:10:37 2011 (+0200)
 * Version: $Id$
 * Last-Updated: mer. avril 11 16:48:30 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 257
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkLog/dtkLog.h>

#include "dtkComposerEvaluatorSlave.h"

#include <dtkCore>

#include <dtkDistributed/dtkDistributedCommunicator.h>
#include <dtkDistributed/dtkDistributedCommunicatorMpi.h>
#include <dtkDistributed/dtkDistributedCommunicatorTcp.h>

#include <QtCore>
#include <QtGui>

int main(int argc, char **argv)
{

    if(argc != 2) {
        qDebug() << "Usage: " << argv[0] << " <server>";
        return 0;
    }

    QUrl url = QUrl(argv[1]);
    bool useGUI = false;

    QApplication application(argc, argv, useGUI);
    application.setApplicationName("dtkComposerEvaluatorSlave");
    application.setApplicationVersion("0.0.2");
    application.setOrganizationName("inria");
    application.setOrganizationDomain("fr");

    dtkLogger::instance().setLevel(dtkLog::Trace);
    dtkLogger::instance().attachFile(dtkLogPath(&application));

    dtkPluginManager::instance()->initialize();

    dtkDistributedCommunicatorMpi *communicator =  new dtkDistributedCommunicatorMpi;
    communicator->initialize();

    dtkComposerEvaluatorSlave *slave = new dtkComposerEvaluatorSlave;



    slave->setInternalCommunicator(communicator);
    slave->setServer(url);
    int value = slave->exec();

    dtkPluginManager::instance()->uninitialize();

    if (communicator->initialized())
        communicator->uninitialize();
    return value;
}
