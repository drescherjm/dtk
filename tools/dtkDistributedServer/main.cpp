/* @(#)main.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2014 - Nicolas Niclausse, Inria.
 * Created: 2014/04/25 16:28:19
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */



#include <dtkCore/dtkCore.h>
#include <dtkDistributed/dtkDistributedServerDaemon.h>
#include <dtkLog/dtkLogger.h>

#include <QCoreApplication>


int main(int argc, char **argv)
{
    QCoreApplication application(argc, argv);


    if(!dtkApplicationArgumentsContain(&application, "-type")) {
        qDebug() << "Usage:" << argv[0] << " [-p port] -type <Oar | Torque | Local |...>";
        return 1;
    }
    int port;
    if(dtkApplicationArgumentsContain(&application, "-p"))
        port = dtkApplicationArgumentsValue(&application, "-p").toInt();
    else
        port = 9999;

    application.setApplicationName("dtkDistributedServer");
    application.setApplicationVersion("0.0.1");
    application.setOrganizationName("inria");
    application.setOrganizationDomain("fr");

    qDebug() << "Starting dtkDistributedServer"; // DO NOT REMOVE THIS
//    qInstallMessageHandler(dtkMessageOutput);

    QSettings settings("inria", "dtk");
    settings.beginGroup("server");

    dtkDistributedServerDaemon server(port);

    server.setManager( dtkApplicationArgumentsValue(&application, "-type"));
    qDebug() << "server started";

    int status = application.exec();

    return status;
}

