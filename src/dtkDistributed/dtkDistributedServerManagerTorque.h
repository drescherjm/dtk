/* dtkDistributedServerManagerTorque.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue May 31 23:08:25 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Jun 28 14:26:23 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 12
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDSERVERMANAGERTORQUE_H
#define DTKDISTRIBUTEDSERVERMANAGERTORQUE_H

#include "dtkDistributedExport.h"
#include "dtkDistributedServerManager.h"

class dtkDistributedServerManagerTorquePrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedServerManagerTorque : public dtkDistributedServerManager
{
    Q_OBJECT

public slots:
    QString status(void);
};

#endif
