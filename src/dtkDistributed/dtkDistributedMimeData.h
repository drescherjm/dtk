/* dtkDistributedMimeData.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Apr 12 11:26:14 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Apr 12 11:44:44 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 15
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

class dtkDistributedMimeData : public QMimeData
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
