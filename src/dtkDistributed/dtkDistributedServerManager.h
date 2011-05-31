/* dtkDistributedServerManager.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue May 31 23:00:53 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue May 31 23:36:43 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 11
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDSERVERMANAGER_H
#define DTKDISTRIBUTEDSERVERMANAGER_H

#include "dtkDistributedExport.h"

#include <QtCore>

class dtkDistributedNode;
class dtkDistributedCpu;
class dtkDistributedGpu;
class dtkDistributedCore;
class dtkDistributedServerManagerPrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedServerManager : public QObject
{
    Q_OBJECT

public:
             dtkDistributedServerManager(void);
    virtual ~dtkDistributedServerManager(void);

    QList<dtkDistributedNode *> nodes(void);
    QList<dtkDistributedCpu *> cpus(void);
    QList<dtkDistributedGpu *> gpus(void);
    QList<dtkDistributedCore *> cores(void);

    bool available(dtkDistributedNode *node, int duration = 60);
    bool available(dtkDistributedCpu *cpu, int duration = 60);
    bool available(dtkDistributedGpu *gpu, int duration = 60);
    bool available(dtkDistributedCore *core, int duration = 60);

public slots:
    virtual void discover(const QUrl& url) = 0;

protected:
    dtkDistributedServerManagerPrivate *d;
};

#endif
