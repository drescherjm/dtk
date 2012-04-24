/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Oct 27 14:10:37 2011 (+0200)
 * Version: $Id$
 * Last-Updated: mar. avril 24 15:11:17 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 264
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

    QSettings settings("inria", "dtk");
    settings.beginGroup("slave");

    if (settings.contains("log_level"))
        dtkLogger::instance().setLevel(settings.value("log_level").toString());
    else
        dtkLogger::instance().setLevel(dtkLog::Trace);

    dtkLogger::instance().attachFile(dtkLogPath(&application));

    dtkPluginManager::instance()->initialize();

    dtkDistributedCommunicatorMpi *communicator =  new dtkDistributedCommunicatorMpi;
    communicator->initialize();

    dtkComposerEvaluatorSlave *slave = new dtkComposerEvaluatorSlave;



    slave->setInternalCommunicator(communicator);
    slave->setServer(url);

    int value;
    do value = slave->exec(); while (value  == 0);

    dtkPluginManager::instance()->uninitialize();

    if (communicator->initialized())
        communicator->uninitialize();
    return value;
}
