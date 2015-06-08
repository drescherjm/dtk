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
    dtkApplication *application = dtkApplication::create(argc, argv);
    application->setApplicationName("dtkDistributedServer");
    application->setApplicationVersion("1.0.0");
    application->setOrganizationName("inria");
    application->setOrganizationDomain("fr");

    QCommandLineParser *parser = application->parser();

    parser->setApplicationDescription("DTK distributed server application.");
    QCommandLineOption typeOption("type", QCoreApplication::translate("main", "type of server "),"Oar| Torque| Local");
    parser->addOption(typeOption);
    int port = 9999;
    QCommandLineOption portOption("p", QCoreApplication::translate("main", "listen port"), QString::number(port));
    parser->addOption(portOption);

    application->initialize();

    if(!parser->isSet(typeOption)) {
        qCritical() << "Error, no type set" ;
        return 1;
    }
    if(parser->isSet(portOption)) {
        port = parser->value(portOption).toInt();
    }


    qDebug() << "Starting dtkDistributedServer"; // DO NOT REMOVE THIS

    QSettings settings("inria", "dtk");
    settings.beginGroup("server");
    if (settings.contains("log_level"))
        dtkLogger::instance().setLevel(settings.value("log_level").toString());
     settings.endGroup();

    dtkDistributedServerDaemon server(port);
    server.setManager( parser->value(typeOption));
    qDebug() << "server started";

    int status = qApp->exec();

    return status;
}
