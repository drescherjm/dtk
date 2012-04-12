/* dtkDistributedControllerJobView.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Apr 11 16:18:04 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Apr 12 09:41:30 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 18
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDCONTROLLERJOBVIEW_H
#define DTKDISTRIBUTEDCONTROLLERJOBVIEW_H

#include "dtkDistributedExport.h"

#include <QtGui>

class dtkDistributedController;
class dtkDistributedControllerJobViewPrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedControllerJobView : public QTreeWidget
{
    Q_OBJECT

public:
     dtkDistributedControllerJobView(QWidget *parent = 0);
    ~dtkDistributedControllerJobView(void);

public:
    void setController(dtkDistributedController *controller);

protected slots:
    void onStatus(const QUrl& cluster);
    void onDisconnected(const QUrl& cluster);

protected:
    void update(void);

private:
    dtkDistributedControllerJobViewPrivate *d;
};

#endif
