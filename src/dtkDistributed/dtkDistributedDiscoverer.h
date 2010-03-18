/* dtkDistributedDiscoverer.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Feb 16 13:21:10 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Mar 17 09:55:24 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 19
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDDISCOVERER_H
#define DTKDISTRIBUTEDDISCOVERER_H

#include <QtCore>
#include <QtNetwork>

#include "dtkDistributedExport.h"

class dtkDistributedNode;
class dtkDistributedCpu;
class dtkDistributedGpu;
class dtkDistributedCore;
class dtkDistributedDiscovererPrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedDiscoverer : public QObject
{
    Q_OBJECT

public:
     dtkDistributedDiscoverer(void);
    ~dtkDistributedDiscoverer(void);

    virtual void discover(const QUrl& url) = 0;

    QList<dtkDistributedNode *> nodes(void);
    QList<dtkDistributedCpu *> cpus(void);
    QList<dtkDistributedGpu *> gpus(void);
    QList<dtkDistributedCore *> cores(void);

    bool available(dtkDistributedNode *node, int duration = 60);
    bool available(dtkDistributedCpu *cpu, int duration = 60);
    bool available(dtkDistributedGpu *gpu, int duration = 60);
    bool available(dtkDistributedCore *core, int duration = 60);

protected:
    dtkDistributedDiscovererPrivate *d;
};

#endif
