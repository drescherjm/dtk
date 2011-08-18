/* dtkDistributedServerManagerOar.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue May 31 23:08:25 2011 (+0200)
 * Version: $Id$
 * Last-Updated: jeu. août 11 10:25:35 2011 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 15
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDSERVERMANAGEROAR_H
#define DTKDISTRIBUTEDSERVERMANAGEROAR_H

#include "dtkDistributedExport.h"
#include "dtkDistributedServerManager.h"

class dtkDistributedServerManagerOarPrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedServerManagerOar : public dtkDistributedServerManager
{
    Q_OBJECT

public slots:
    QString status(void);
    QString submit(QString input);
    QString deljob(QString input);
};

#endif
