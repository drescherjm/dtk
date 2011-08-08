/* dtkDistributedServerManager.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue May 31 23:00:53 2011 (+0200)
 * Version: $Id$
 * Last-Updated: mer. juin 29 11:27:34 2011 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 26
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

    static QString protocol(void) { return "1.0"; };

public slots:
    virtual QString status(void) = 0;
    virtual QString submit(QString input) = 0;

protected:
    dtkDistributedServerManagerPrivate *d;
};

#endif
