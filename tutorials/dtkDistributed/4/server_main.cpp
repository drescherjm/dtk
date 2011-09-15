/* server_main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Sep 14 13:20:15 2011 (+0200)
 * Version: $Id$
 * Last-Updated: jeu. sept. 15 13:55:19 2011 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 155
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
    QCoreApplication application(argc,argv) ;

    dtkDistributedServer server(argc, argv);

    server.run();

    QVariantMap job;
    QVariantMap resources;
    resources.insert("cores", 2);
    resources.insert("nodes", 2);
    job.insert("resources", resources);
    QString scriptName=qApp->applicationDirPath()+"/dtkDistributedServerScript.sh";
    job.insert("script", scriptName);
    job.insert("walltime", "1:0:0");
    QString data = dtkJson::serialize(job);
    dtkDistributedServerManager *  manager = server.manager();

    QFile script(scriptName);
    if (!script.open(QFile::WriteOnly|QFile::Truncate)) {
        qDebug() << "unable to open script for writing";
    } else {
        QTextStream out(&script);
        out << "#!/bin/bash\n";
        out << "mpirun " +qApp->applicationDirPath()+"/"+"dtkDistributedTutorial4Slave "+"10000"+ "  --server " + "dtk://nef-devel:9999";
    }
    script.close();

    QString jobid = manager->submit(data);
    qDebug() << DTK_PRETTY_FUNCTION << "Job Id is: " << jobid;


    int status = application.exec();
    QDir::current()->remove(scriptName);
    return status;
}
