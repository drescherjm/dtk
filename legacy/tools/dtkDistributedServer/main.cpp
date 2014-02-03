/* @(#)main.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/04/03 14:41:29
 * Version: $Id$
 * Last-Updated: mer. avril 25 13:08:30 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 13
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */


#include <dtkCore>
#include <dtkDistributed>

#include <dtkLog/dtkLog.h>

#include <QtCore>

int main(int argc, char **argv)
{
    QCoreApplication application(argc, argv);

    if(!dtkApplicationArgumentsContain(&application, "--torque")
       && !dtkApplicationArgumentsContain(&application, "--oar")
       && !dtkApplicationArgumentsContain(&application, "--ssh")) {
        qDebug() << "Usage:" << argv[0] << " dtk://server:port [--oar || --torque || --ssh]";
        return DTK_SUCCEED;
    }

    application.setApplicationName("dtkDistributedServer");
    application.setApplicationVersion("0.0.1");
    application.setOrganizationName("inria");
    application.setOrganizationDomain("fr");

    QSettings settings("inria", "dtk");
    settings.beginGroup("server");

    if (settings.contains("log_level"))
        dtkLogger::instance().setLevel(settings.value("log_level").toString());
    else
        dtkLogger::instance().setLevel(dtkLog::Debug);

    dtkLogger::instance().attachFile(dtkLogPath(&application));

    dtkDistributedServer server(argc, argv);
    qDebug() << "server started";
    server.run();

    int status = application.exec();

    return status;
}

