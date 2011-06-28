/* dtkDistributedServerManagerTorque.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue May 31 23:10:24 2011 (+0200)
 * Version: $Id$
 * Last-Updated: mar. juin 28 16:21:24 2011 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 233
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedCore.h"
#include "dtkDistributedCpu.h"
#include "dtkDistributedGpu.h"
#include "dtkDistributedNode.h"
#include "dtkDistributedServerManager_p.h"
#include "dtkDistributedServerManagerTorque.h"

#include <dtkCore/dtkGlobal.h>
#include <dtkCore/dtkLog.h>

#include <QtCore>
#include <QtXml>

QString dtkDistributedServerManagerTorque::status(void)
{
    QProcess stat; stat.start("pbsnodes", QStringList() << "-x");

    if (!stat.waitForStarted()) {
        dtkCritical() << "Unable to launch stat command";
        return QString();
    }

    if (!stat.waitForFinished()) {
        dtkCritical() << "Unable to completed stat command";
        return QString();
    }

    QString result = "status;" + protocol() +"\n";
    QString data = stat.readAll();
    QDomDocument document; QString error;

    if(!document.setContent(data, false, &error))
      dtkDebug() << "Error retrieving xml output out of torque "  << error;

    QDomNodeList nodes = document.elementsByTagName("Node");
    for(int i = 0; i < nodes.count(); i++) {
      QString np = nodes.item(i).firstChildElement("np").text().simplified();
      QString name = nodes.item(i).firstChildElement("name").text().simplified();
      QString state = nodes.item(i).firstChildElement("state").text().simplified();

      // Each job is coreid/jobid, count the number of "/" to get the number of jobs
      int njobs  = nodes.item(i).firstChildElement("jobs").text().simplified().count("/");
      QString ngpus  = nodes.item(i).firstChildElement("gpus").text().simplified();

      // number of busy GPUs not implemented
      QStringList properties = nodes.item(i).firstChildElement("properties").text().simplified().split(",");

      QStringList outprops;
      QString prop;
      // FIXME: we should read the properties mapping from a file instead of hardcoding it
      outprops << "infiniband=QDR";
      outprops << "ethernet=1G";
      foreach( prop, properties ) {
        if (prop.contains("opteron")) {
          outprops << "arch=opteron";
        } else if (prop.contains("xeon")) {
          outprops << "arch=xeon";
        } else if (prop.contains("C2050")) {
          outprops << "gpu=nvidia-C2050";
        } else if (prop.contains("T10")) {
          outprops << "gpu=nvidia-T10";
        } else if (prop.contains("T10")) {
          outprops << "gpu=nvidia-T10";
        }
      }
      result += name + ";" + np + ";" + QString::number(njobs) + ";" + ngpus + ";0;" + "("+outprops.join(",")+");";
      if (state.contains("job-exclusive")) {
        state="busy";
      } else if (state.contains("free")) {
        state="free";
      } else {
        state="down";
      }
      result += state+"\n";
    }

    result += "endstatus\n";
    return result;
}
