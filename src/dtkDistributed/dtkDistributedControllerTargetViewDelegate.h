/* dtkDistributedControllerTargetViewDelegate.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Apr  6 10:04:27 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Apr  6 10:55:34 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 30
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDCONTROLLERTARGETVIEWDELEGATE_H
#define DTKDISTRIBUTEDCONTROLLERTARGETVIEWDELEGATE_H

#include "dtkDistributedExport.h"

#include <QtGui>

class dtkDistributedController;

// /////////////////////////////////////////////////////////////////
// dtkDistributedControllerTargetViewDelegate
// /////////////////////////////////////////////////////////////////

class dtkDistributedControllerTargetViewDelegatePrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedControllerTargetViewDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
     dtkDistributedControllerTargetViewDelegate(QWidget *parent = 0);
    ~dtkDistributedControllerTargetViewDelegate(void);

public:
    void setController(dtkDistributedController *controller); 

public:
    void paint(QPainter *painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;

public:
    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const;

public:
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;

public:
    void setEditorData(QWidget *editor, const QModelIndex& index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex& index) const;

private:
    dtkDistributedControllerTargetViewDelegatePrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkDistributedControllerTargetViewEditor
// /////////////////////////////////////////////////////////////////

class dtkDistributedControllerTargetViewEditorPrivate;

class dtkDistributedControllerTargetViewEditor : public QWidget
{
    Q_OBJECT

public:
     dtkDistributedControllerTargetViewEditor(QWidget *parent = 0);
    ~dtkDistributedControllerTargetViewEditor(void);

public:
    void setController(dtkDistributedController *controller);
    void setCluster(QUrl cluster);

protected slots:
    void onRefresh(void);
    void onDisconnect(void);

private:
    dtkDistributedControllerTargetViewEditorPrivate *d;
};

#endif
