/* dtkDistributedController.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed May 25 14:13:03 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Wed May 25 17:03:30 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 11
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDCONTROLLER_H
#define DTKDISTRIBUTEDCONTROLLER_H

#include "dtkDistributedExport.h"

#include <QtCore>

class dtkDistributedControllerPrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedController : public QObject
{
    Q_OBJECT

public:
     dtkDistributedController(void);
    ~dtkDistributedController(void);

public slots:
    void connect(const QUrl& server);

private:
    dtkDistributedControllerPrivate *d;
};

#endif
