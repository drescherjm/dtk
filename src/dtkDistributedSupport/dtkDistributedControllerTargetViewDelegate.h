/* dtkDistributedControllerTargetViewDelegate.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Apr  6 10:04:27 2012 (+0200)
 * Version: $Id$
 * Last-Updated: mar. oct. 30 16:46:58 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 31
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKDISTRIBUTEDCONTROLLERTARGETVIEWDELEGATE_H
#define DTKDISTRIBUTEDCONTROLLERTARGETVIEWDELEGATE_H

#include "dtkDistributedSupportExport.h"

#include <QtWidgets>

class dtkDistributedController;

// /////////////////////////////////////////////////////////////////
// dtkDistributedControllerTargetViewDelegate
// /////////////////////////////////////////////////////////////////

class dtkDistributedControllerTargetViewDelegatePrivate;

class DTKDISTRIBUTEDSUPPORT_EXPORT dtkDistributedControllerTargetViewDelegate : public QStyledItemDelegate
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
    void onStop(void);

private:
    dtkDistributedControllerTargetViewEditorPrivate *d;
};

#endif
