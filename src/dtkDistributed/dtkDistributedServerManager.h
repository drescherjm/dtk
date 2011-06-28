/* dtkDistributedServerManager.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue May 31 23:00:53 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Jun 28 14:26:04 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 16
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

    enum Type {
        Oar,
        Torque
    };

public slots:
    virtual QString status(void) = 0;

protected:
    dtkDistributedServerManagerPrivate *d;
};

#endif
