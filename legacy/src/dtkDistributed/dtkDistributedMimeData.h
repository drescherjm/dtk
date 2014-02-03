/* dtkDistributedMimeData.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Apr 12 11:26:14 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Apr 16 12:15:37 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 16
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDMIMEDATA_H
#define DTKDISTRIBUTEDMIMEDATA_H

#include "dtkDistributedExport.h"

#include <QtGui>

class dtkDistributedController;
class dtkDistributedMimeDataPrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedMimeData : public QMimeData
{
    Q_OBJECT

public:
     dtkDistributedMimeData(void);
    ~dtkDistributedMimeData(void);

public:
    dtkDistributedController *controller(void);

public:
    void setController(dtkDistributedController *controller);

private:
    dtkDistributedMimeDataPrivate *d;
};

#endif
