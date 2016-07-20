// Version: $Id$
//
//

// Commentary:
//
//

// Change Log:
//
//

// Code:

#pragma once

#include "dtkComposerExport.h"

#include <QtGui>
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

//
// dtkComposerControlsDelegate.h ends here
