/* dtkDistributedCore.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Feb 16 16:24:27 2010 (+0100)
 * Version: $Id$
 * Last-Updated: mer. août 10 12:36:15 2011 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 36
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

#include "dtkDistributedExport.h"

class dtkDistributedCpu;
class dtkDistributedJob;
class dtkDistributedCorePrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedCore : public QObject
{
    Q_OBJECT

public:
     dtkDistributedCore(dtkDistributedCpu *parent);
    ~dtkDistributedCore(void);

     dtkDistributedJob* job(void);
     void setJob(dtkDistributedJob *job );
     void delJob(void);

private:
    dtkDistributedCorePrivate *d;
};

#endif
