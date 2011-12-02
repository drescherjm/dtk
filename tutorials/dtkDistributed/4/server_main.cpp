/* server_main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Sep 14 13:20:15 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Nov 23 09:52:33 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 313
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */


#include <QtGui>
#include <QtDebug>
#include <QtCore>

#include <dtkCore/dtkLog.h>
#include <dtkCore/dtkGlobal.h>

#include <dtkJson/dtkJson.h>

#include <dtkDistributed/dtkDistributedServer.h>
#include <dtkDistributed/dtkDistributedServerManager.h>

int main(int argc, char **argv)
{
    QCoreApplication application(argc, argv);

    if(!dtkApplicationArgumentsContain(&application, "--torque")
    && !dtkApplicationArgumentsContain(&application, "--oar")) {
        dtkDebug() << "Usage:" << argv[0] << " dtk://server:port [--oar || --torque]";
        return DTK_SUCCEED;
    }

// /////////////////////////////////////////////////////////////////
// Instantiate a server
// /////////////////////////////////////////////////////////////////

    dtkDistributedServer server(argc, argv);
    server.run();

// /////////////////////////////////////////////////////////////////
// Create a dummy job description. To be serialized at the time of the
// submission. For academic purposes only.
/////////////////////////////////////////////////////////////////

    QString scriptName = qApp->applicationDirPath() + "/dtkDistributedServerScript.sh";

    QVariantMap resources;
    resources.insert("cores", 2);
    resources.insert("nodes", 2);

    QVariantMap job;
    job.insert("resources", resources);
    job.insert("script", scriptName);
    job.insert("walltime", "1:0:0");

    QFile script(scriptName);

    if (!script.open(QFile::WriteOnly|QFile::Truncate)) {
        qDebug() << "unable to open script for writing";
    } else {
        QTextStream out(&script);
        out << "#!/bin/bash\n";
        out << "mpirun "
            + qApp->applicationDirPath()
            + "/dtkDistributedTutorial4Slave "
            + "10000 "
            + "--server "
            + argv[1];
    }

    script.close();

// /////////////////////////////////////////////////////////////////
// Submit the job
// /////////////////////////////////////////////////////////////////

    dtkDistributedServerManager *manager = server.manager();

    QString jobid = manager->submit(dtkJson::serialize(job));

    server.waitForConnection(0);

// /////////////////////////////////////////////////////////////////
// Server waits for result on rank 0.
// /////////////////////////////////////////////////////////////////

    QByteArray res = server.waitForData(0);

    qDebug() << "result is " << res;

    script.remove();

    return DTK_SUCCEED;
}
