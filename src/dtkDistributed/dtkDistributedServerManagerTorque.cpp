/* dtkDistributedServerManagerTorque.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue May 31 23:10:24 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Jun 28 14:32:13 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 53
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
    
    QString result = stat.readAll();

    return result;
}
