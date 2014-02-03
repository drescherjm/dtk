/* dtkDistributedCore.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Feb 16 16:24:27 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Apr  5 10:15:27 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 47
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDCORE_H
#define DTKDISTRIBUTEDCORE_H

#include <QObject>

#include "dtkDistributedSupportExport.h"

class dtkDistributedCpu;
class dtkDistributedJob;
class dtkDistributedCorePrivate;

class DTKDISTRIBUTEDSUPPORT_EXPORT dtkDistributedCore : public QObject
{
    Q_OBJECT

public:
     dtkDistributedCore(dtkDistributedCpu *parent, qint64 id);
    ~dtkDistributedCore(void);

public:
    dtkDistributedJob *job(void);

public:
    void setJob(dtkDistributedJob *job);
    void delJob(void);
    
private:
    dtkDistributedCorePrivate *d;
};

#endif
