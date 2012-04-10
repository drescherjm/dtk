/* dtkDistributedControllerFilterView.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Apr 10 10:10:19 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Apr 10 18:15:26 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 30
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDCONTROLLERFILTERVIEW_H
#define DTKDISTRIBUTEDCONTROLLERFILTERVIEW_H

#include "dtkDistributedExport.h"
#include "dtkDistributedNode.h"
#include "dtkDistributedCpu.h"

#include <QtGui>

class dtkDistributedControllerFilterViewPrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedControllerFilterView : public QTreeWidget
{
    Q_OBJECT

public:
     dtkDistributedControllerFilterView(QWidget *parent = 0);
    ~dtkDistributedControllerFilterView(void);

signals:
    void updated(void);

public:
    QFlags<dtkDistributedNode::Network> networkFlags(void);
    QFlags<dtkDistributedNode::State> stateFlags(void);
    QFlags<dtkDistributedNode::Brand> brandFlags(void);
    QFlags<dtkDistributedCpu::Architecture> archFlags(void);
    QFlags<dtkDistributedCpu::Model> modelFlags(void);

private slots:
    void onNetworkButtonClicked(int);
    void onStateButtonClicked(int);
    void onBrandButtonClicked(int);
    void onArchButtonClicked(int);
    void onModelButtonClicked(int);

private:
    dtkDistributedControllerFilterViewPrivate *d;
};

#endif
