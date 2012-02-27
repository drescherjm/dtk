/* dtkComposerFactoryView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Tue Jan 31 13:24:50 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Sat Feb 25 00:48:55 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 65
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
    QTreeWidgetItem *nodes_p;
    QTreeWidgetItem *nodes_c;
    QTreeWidgetItem *note;
};

dtkComposerFactoryView::dtkComposerFactoryView(QWidget *parent) : QTreeWidget(parent), d(new dtkComposerFactoryViewPrivate)
{
    d->factory = NULL;

    d->nodes_p = new QTreeWidgetItem(this, QStringList() << "Primitive nodes");
    d->nodes_p->setExpanded(true);

    d->nodes_c = new QTreeWidgetItem(this, QStringList() << "Control nodes");
    d->nodes_c->setExpanded(true);

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

    foreach(QString node, d->factory->primitives().keys()) {
        QTreeWidgetItem *item = new QTreeWidgetItem(d->nodes_p, QStringList() << node);
        item->setData(0, Qt::UserRole, QUrl(QString("node:%1").arg(d->factory->primitives().value(node))));
        // this->addTopLevelItem(item);
    }

    foreach(QString node, d->factory->controls().keys()) {
        QTreeWidgetItem *item = new QTreeWidgetItem(d->nodes_c, QStringList() << node);
        item->setData(0, Qt::UserRole, QUrl(QString("node:%1").arg(d->factory->controls().value(node))));
        // this->addTopLevelItem(item);
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
