/* dtkDistributor.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Apr  3 16:33:58 2012 (+0200)
 * Version: $Id$
 * Last-Updated: mer. mai 23 17:46:30 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 19
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTOR_H
#define DTKDISTRIBUTOR_H

#include "dtkDistributedSupportExport.h"

#include <QtWidgets>

class dtkDistributorPrivate;

class DTKDISTRIBUTEDSUPPORT_EXPORT dtkDistributor : public QFrame
{
    Q_OBJECT

public:
     dtkDistributor(QWidget *parent = 0);
    ~dtkDistributor(void);

public:
    void setApplication(const QString& application);

protected slots:
    void onConnect(void);
    void onFilterUpdated(void);

private:
    dtkDistributorPrivate *d;
};

#endif
