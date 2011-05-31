/* dtkDistributedServerManager.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue May 31 23:00:53 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue May 31 23:14:55 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 7
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

#include <QtCore/QObject>
#include <QtCore/QUrl>

class dtkDistributedServerManagerPrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedServerManager : public QObject
{
    Q_OBJECT

public:
             dtkDistributedServerManager(void);
    virtual ~dtkDistributedServerManager(void);

public slots:
    virtual void discover(const QUrl& url) = 0;

private:
    dtkDistributedServerManagerPrivate *d;
};

#endif
