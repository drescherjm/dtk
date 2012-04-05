/* dtkDistributedControllerTargetView.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Apr  4 12:25:27 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Apr  5 14:24:38 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 10
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDCONTROLLERTARGETVIEW_H
#define DTKDISTRIBUTEDCONTROLLERTARGETVIEW_H

#include "dtkDistributedExport.h"

#include <QtGui>

class dtkDistributedController;
class dtkDistributedControllerTargetViewPrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedControllerTargetView : public QListWidget
{
    Q_OBJECT

public:
     dtkDistributedControllerTargetView(QWidget *parent = 0);
    ~dtkDistributedControllerTargetView(void);

public:
    QSize sizeHint(void) const;

public:
    void setController(dtkDistributedController *controller);

protected slots:
    void onConnected(const QUrl& server);

private:
    dtkDistributedControllerTargetViewPrivate *d;
};

#endif
