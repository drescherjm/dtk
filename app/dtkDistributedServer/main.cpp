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
    QCoreApplication::setApplicationName("dtkDistributedServer");
    QCoreApplication::setApplicationVersion("1.0.0");

    QCommandLineParser parser;
    parser.setApplicationDescription("DTK distributed server application.");
    parser.addHelpOption();
    parser.addVersionOption();
    QCommandLineOption typeOption("type", QCoreApplication::translate("main", "type of server: Oar, Torque, Local, ..."));
    parser.addOption(typeOption);
    int port = 9999;
    QCommandLineOption portOption("p", QCoreApplication::translate("main", "listen port"), QString::number(port));
    parser.addOption(portOption);

    if (!parser.parse(QCoreApplication::arguments())) {
        qCritical() << "Command line error" ;
        return 1;
    }

    parser.process(application);

    if(!parser.isSet(typeOption)) {
        qDebug() << "Error, no type set" ;
        return 1;
    }
    if(parser.isSet(portOption)) {
        port = parser.value(portOption).toInt();
    }

    application.setApplicationName("dtkDistributedServer");
    application.setApplicationVersion("0.0.1");
    application.setOrganizationName("inria");
    application.setOrganizationDomain("fr");

    qDebug() << "Starting dtkDistributedServer"; // DO NOT REMOVE THIS
//    qInstallMessageHandler(dtkMessageOutput);

    QSettings settings("inria", "dtk");
    settings.beginGroup("server");

    dtkDistributedServerDaemon server(port);

    server.setManager( parser.value(typeOption));
    qDebug() << "server started";

    int status = application.exec();

    return status;
}
