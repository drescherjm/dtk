/* dtkComposerFactoryView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jan 31 13:24:50 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Feb  2 10:11:10 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 38
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerFactory.h"
#include "dtkComposerFactoryView.h"

class dtkComposerFactoryViewPrivate
{
public:
    dtkComposerFactory *factory;

public:
    QTreeWidgetItem *root;
    QTreeWidgetItem *note;
};

dtkComposerFactoryView::dtkComposerFactoryView(QWidget *parent) : QTreeWidget(parent), d(new dtkComposerFactoryViewPrivate)
{
    d->factory = NULL;

    d->root = new QTreeWidgetItem(this, QStringList() << "Nodes");
    d->root->setExpanded(true);

    d->note = new QTreeWidgetItem(this, QStringList() << "Note");
    d->note->setData(0, Qt::UserRole, QUrl(QString("note://")));

    this->setAttribute(Qt::WA_MacShowFocusRect, false);
    this->setCursor(Qt::ArrowCursor);
    this->setDragEnabled(true);
    this->setFrameShape(QFrame::NoFrame);
    this->setHeaderHidden(true);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

dtkComposerFactoryView::~dtkComposerFactoryView(void)
{
    delete d;

    d = NULL;
}

void dtkComposerFactoryView::setFactory(dtkComposerFactory *factory)
{
    d->factory = factory;

    foreach(QString node, d->factory->nodes().keys())
        this->addItem(node, d->factory->nodes().value(node));
}

void dtkComposerFactoryView::addItem(const QString& node, const QString& type)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(d->root, QStringList() << node);
    item->setData(0, Qt::UserRole, QUrl(QString("node:%1").arg(type)));

    this->addTopLevelItem(item);
}

void dtkComposerFactoryView::filter(const QString& text)
{
    for(int i = 0; i < d->root->childCount(); i++) {
        if (d->root->child(i)->text(0).contains(text))
            d->root->child(i)->setHidden(false);
        else
            d->root->child(i)->setHidden(true);
    }
}

QMimeData *dtkComposerFactoryView::mimeData(const QList<QTreeWidgetItem *> items) const
{
    QMimeData *data = NULL;

    QTreeWidgetItem *item = items.first();

    if(item) {
        data = new QMimeData;
        data->setText(item->text(0));
        data->setUrls(QList<QUrl>() << item->data(0, Qt::UserRole).toUrl());
    }

    return data;
}

QStringList dtkComposerFactoryView::mimeTypes(void) const
{
    return QStringList() << "text/uri-list";
}
