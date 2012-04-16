/* dtkDistributor.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Apr  3 16:33:58 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Apr 11 13:33:25 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 13
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTOR_H
#define DTKDISTRIBUTOR_H

#include "dtkDistributedExport.h"

#include <QtGui>

class dtkDistributorPrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributor : public QFrame
{
    Q_OBJECT

public:
     dtkDistributor(QWidget *parent = 0);
    ~dtkDistributor(void);

protected slots:
    void onConnect(void);
    void onFilterUpdated(void);

private:
    dtkDistributorPrivate *d;
};

#endif
