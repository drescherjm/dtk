/* dtkDistributedControllerTargetView.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Apr  4 12:25:27 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Apr 11 16:45:55 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 19
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDCONTROLLERTARGETVIEW_H
#define DTKDISTRIBUTEDCONTROLLERTARGETVIEW_H

#include "dtkDistributedSupportExport.h"

#include <QtWidgets>

class dtkDistributedController;
class dtkDistributedControllerTargetViewPrivate;

class DTKDISTRIBUTEDSUPPORT_EXPORT dtkDistributedControllerTargetView : public QListWidget
{
    Q_OBJECT

public:
     dtkDistributedControllerTargetView(QWidget *parent = 0);
    ~dtkDistributedControllerTargetView(void);

public:
    QSize sizeHint(void) const;

public:
    void setController(dtkDistributedController *controller);

signals:
    void selected(const QString& server);

protected slots:
    void onConnected(const QUrl& server);
    void onDisconnected(const QUrl& server);

protected slots:
    void onItemClicked(QListWidgetItem *item);

private:
    dtkDistributedControllerTargetViewPrivate *d;
};

#endif
