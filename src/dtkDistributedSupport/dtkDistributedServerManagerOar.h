/* dtkDistributedServerManagerOar.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue May 31 23:08:25 2011 (+0200)
 * Version: $Id$
 * Last-Updated: mar. sept. 20 15:08:12 2011 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 16
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDSERVERMANAGEROAR_H
#define DTKDISTRIBUTEDSERVERMANAGEROAR_H

#include "dtkDistributedSupportExport.h"
#include "dtkDistributedServerManager.h"

class dtkDistributedServerManagerOarPrivate;

class DTKDISTRIBUTEDSUPPORT_EXPORT dtkDistributedServerManagerOar : public dtkDistributedServerManager
{
    Q_OBJECT

public slots:
    QByteArray status(void);
    QString submit(QString input);
    QString deljob(QString input);
};

#endif
