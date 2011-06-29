/* dtkDistributedServerManagerTorque.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue May 31 23:08:25 2011 (+0200)
 * Version: $Id$
 * Last-Updated: mer. juin 29 17:50:09 2011 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 16
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
};

#endif
