/* dtkComposerControlsDelegate.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Nov 28 15:06:31 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Apr 11 10:33:43 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 58
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#pragma once

#include "dtkComposerExport.h"

#include <QtWidgets>

class dtkComposerControlsDelegatePrivate;

class DTKCOMPOSER_EXPORT dtkComposerControlsDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
     dtkComposerControlsDelegate(QObject *parent = 0);
    ~dtkComposerControlsDelegate(void);

public:
    void paint(QPainter *painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
public:
    void setEditorData(QWidget *editor, const QModelIndex& index ) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex& index) const;

public:
    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const;

public:
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem& option, const QModelIndex& index) const;

private:
    dtkComposerControlsDelegatePrivate *d;
};

