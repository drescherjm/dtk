/* dtkDistributedServerManagerTorque.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue May 31 23:08:25 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Sep 19 11:20:25 2011 (+0200)
 *           By: jwintz
 *     Update #: 20
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
    QString submit(QString input);
    QString deljob(QString jobid);
};

#endif
