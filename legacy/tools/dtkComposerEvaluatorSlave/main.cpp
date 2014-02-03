/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Oct 27 14:10:37 2011 (+0200)
 * Version: $Id$
 * Last-Updated: mer. mars 27 17:06:59 2013 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 298
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkLog/dtkLog.h>


#include <dtkCore>

#include <dtkComposer/dtkComposerFactory.h>
#include <dtkComposer/dtkComposerEvaluatorSlave.h>

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

    QSettings settings("inria", "dtk");
    settings.beginGroup("slave");

    if (settings.contains("log_level"))
        dtkLogger::instance().setLevel(settings.value("log_level").toString());
    else
        dtkLogger::instance().setLevel(dtkLog::Trace);

    if (settings.contains("use_gui") && settings.value("use_gui").toString() == "true")
        useGUI = true;

    QApplication application(argc, argv, useGUI);
    application.setApplicationName("dtkComposerEvaluatorSlave");
    application.setApplicationVersion("0.0.2");
    application.setOrganizationName("inria");
    application.setOrganizationDomain("fr");

    dtkLogger::instance().attachFile(dtkLogPath(&application));

    dtkPluginManager::instance()->initialize();

    dtkDistributedCommunicatorMpi *communicator =  new dtkDistributedCommunicatorMpi;
    communicator->initialize();

    dtkComposerEvaluatorSlave *slave = new dtkComposerEvaluatorSlave;
    dtkComposerFactory      *factory = new dtkComposerFactory;
    slave->setInternalCommunicator(communicator);
    slave->setServer(url);
    slave->setFactory(factory);

    int value;
    do  { value = slave->exec(); } while (value  == 0);

    dtkPluginManager::instance()->uninitialize();

    if (communicator->initialized())
        communicator->uninitialize();

    return value;
}
