/* dtkComposerControlsDelegate.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Nov 28 15:06:31 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Nov 28 15:23:11 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 56
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERCONTROLSDELEGATE_H
#define DTKCOMPOSERCONTROLSDELEGATE_H

#include <dtkComposerExport.h>

#include <QtGui>

class dtkComposerControlsDelegatePrivate;

class DTKCOMPOSER_EXPORT dtkComposerControlsDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
     dtkComposerControlsDelegate(QObject *parent = 0);
    ~dtkComposerControlsDelegate(void);

public:
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem& option, const QModelIndex& index ) const;

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

#endif
