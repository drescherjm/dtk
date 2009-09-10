/* dtkUiView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Jun 12 17:32:34 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Sep  9 11:35:24 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 213
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkUiItemDelegate.h"
#include "dtkUiItem.h"
#include "dtkUiView.h"

#include <QtCore>
#include <QtGui>

// /////////////////////////////////////////////////////////////////
// dtkUiViewPrivate
// /////////////////////////////////////////////////////////////////

class dtkUiViewPrivate
{
public:
    QStandardItemModel *model;
    QStandardItem *root;
    QTreeView *tree;
};

dtkUiView::dtkUiView(QWidget *parent) : QTreeView(parent)
{
    d = new dtkUiViewPrivate;

    d->model = new QStandardItemModel;
    d->model->setHorizontalHeaderLabels(QStringList() << "Title");
    d->root = d->model->invisibleRootItem();

    this->setModel(d->model);

    QPalette qPalette = palette();
    qPalette.setColor(QPalette::Base, QColor(0xd1, 0xd6, 0xdc));
    this->setPalette(qPalette);

    this->setItemDelegate(new dtkUiItemDelegate);
    this->setItemsExpandable(false);
    this->setRootIsDecorated(false);
    this->setAutoExpandDelay(0);
    this->setHeaderHidden(true);
    this->setIndentation(0);

    // this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    this->setFrameStyle(QFrame::NoFrame);
    this->setAttribute(Qt::WA_MacShowFocusRect, false);    

    // QHeaderView *header = this->header();
    // header->setStyleSheet(
    //     "QHeaderView::section {"
    //     "   background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 rgb(172, 188, 206), stop:0.5 rgb(129, 156, 181), stop:0.6 rgb(121, 149, 176), stop:1 rgb(101, 133, 164));"
    //     "   color: white;"
    //     "   border: 0px;"
    //     "}");
     
    connect(this, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(booleanDoubleClicked(const QModelIndex&)));
}

dtkUiView::~dtkUiView(void)
{

}

void dtkUiView::append(dtkUiItem *item)
{
    d->root->appendRow(item);

    this->expandAll();
}

QSize dtkUiView::minimumSizeHint(void) const
{
    int count = d->root->rowCount();

    for(int i = 0 ; i < d->root->rowCount() ; i++)
        count += d->root->child(i)->rowCount();

    return QSize(100, 30 + count * 30 + d->root->rowCount() * 5);
}

void dtkUiView::booleanDoubleClicked(const QModelIndex& index)
{
    if (!index.isValid())
        return;
    
    QString keyName = index.data(Qt::DisplayRole).toString();
    int itemType = index.data(Qt::UserRole + 2).toInt();
    QVariant keyValue = index.data(Qt::UserRole + 1);
    
    if (itemType == dtkUiItem::Link) {
        emit linkClicked(keyName, keyValue);
    } else if (itemType == dtkUiItem::MultiValue) {
        emit multiValueClicked(keyName, keyValue);
    } else if (itemType == dtkUiItem::Button) {
        emit buttonClicked(keyName, keyValue);
    } else if (itemType == dtkUiItem::Value) {
        if (keyValue.type() == QVariant::Bool)
            this->model()->setData(index, !keyValue.toBool(), Qt::UserRole + 1);
        else
            emit valueClicked(keyName, keyValue);
    }

    emit updated();
}
