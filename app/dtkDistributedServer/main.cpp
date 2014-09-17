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

#include <dtkDistributed/dtkDistributedServerDaemon.h>
#include <dtkCore>
#include <dtkLog>

#include <QtCore>

int main(int argc, char **argv)
{
    QCoreApplication application(argc, argv);

    if(!dtkCoreApplicationArgumentsContain(&application, "-type")) {
        qDebug() << "Usage:" << argv[0] << " [-p port] -type <Oar | Torque | Local |...>";
        return 1;
    }
    int port;
    if(dtkCoreApplicationArgumentsContain(&application, "-p"))
        port = dtkCoreApplicationArgumentsValue(&application, "-p").toInt();
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

    server.setManager( dtkCoreApplicationArgumentsValue(&application, "-type"));
    qDebug() << "server started";

    int status = application.exec();

    return status;
}
