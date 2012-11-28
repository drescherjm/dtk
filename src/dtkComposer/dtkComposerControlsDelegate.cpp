/* dtkComposerControlsDelegate.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Nov 28 15:12:23 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Nov 28 17:16:25 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 135
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerControls.h"
#include "dtkComposerControlsDelegate.h"

class dtkComposerControlsDelegatePrivate
{
public:
};

dtkComposerControlsDelegate::dtkComposerControlsDelegate(QObject *parent) : QStyledItemDelegate(parent), d(new dtkComposerControlsDelegatePrivate)
{
    
}

dtkComposerControlsDelegate::~dtkComposerControlsDelegate(void)
{
    delete d;

    d = NULL;
}

QWidget *dtkComposerControlsDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QListWidget *list = qobject_cast<QListWidget *>(parent->parent());

    if(!list)
        return QStyledItemDelegate::createEditor(parent, option, index);

    QListWidgetItem *item = list->item(index.row());

    if(!item)
        return QStyledItemDelegate::createEditor(parent, option, index);

    if(item->type() == dtkComposerControls::Integer)
        qDebug() << Q_FUNC_INFO << "integer node";
    else
        qDebug() << Q_FUNC_INFO << "unknown node";

    return QStyledItemDelegate::createEditor(parent, option, index);
}

void dtkComposerControlsDelegate::paint(QPainter *painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QLinearGradient gradient;
    gradient.setStart(option.rect.topLeft());
    gradient.setFinalStop(option.rect.bottomLeft());
    gradient.setColorAt(0, Qt::lightGray);
    gradient.setColorAt(1, Qt::gray);

    painter->save();
    painter->fillRect(option.rect, gradient);
    painter->setPen(QColor("#eeeeee"));
    painter->drawLine(option.rect.topLeft(), option.rect.topRight());
    painter->setPen(Qt::darkGray);
    painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight());
    painter->restore();

    QStyledItemDelegate::paint(painter, option, index);
}

void dtkComposerControlsDelegate::setEditorData(QWidget *editor, const QModelIndex& index) const
{
    QStyledItemDelegate::setEditorData(editor, index);
}

void dtkComposerControlsDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex& index) const
{
    QStyledItemDelegate::setModelData(editor, model, index);
}

QSize dtkComposerControlsDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QSize size = QStyledItemDelegate::sizeHint(option, index);
    size.setHeight(60);

    return size;
}

void dtkComposerControlsDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QStyledItemDelegate::updateEditorGeometry(editor, option, index);
}
