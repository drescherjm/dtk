/* dtkViewList.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed May 16 09:39:06 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Jan 16 16:39:32 2014 (+0100)
 *           By: Selim Kraria
 *     Update #: 27
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkViewList.h"

#include <dtkCore/dtkAbstractView.h>
#include <dtkCore/dtkAbstractViewFactory.h>

class dtkViewListPrivate
{
public:
};

dtkViewList::dtkViewList(QWidget *parent) : QListWidget(parent), d(new dtkViewListPrivate)
{
    this->setAttribute(Qt::WA_MacShowFocusRect, false);
    this->setDragEnabled(true);
    this->setFrameStyle(QFrame::NoFrame);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    this->setFixedHeight(100);

    connect(dtkAbstractViewFactory::instance(), SIGNAL(created(dtkAbstractView *, const QString&)), this, SLOT(update()));

    connect(dtkAbstractViewFactory::instance(), SIGNAL(cleared()), this, SLOT(clear()));

    this->update();
}

dtkViewList::~dtkViewList(void)
{
    delete d;

    d = NULL;
};

void dtkViewList::update(void)
{
    this->clear();

    foreach(QString view, dtkAbstractViewFactory::instance()->viewNames())
        this->addItem(view);
}

void dtkViewList::clear(void)
{
    QListWidget::clear();
}

QMimeData *dtkViewList::mimeData(const QList<QListWidgetItem *> items) const
{
    QMimeData *mimeData = new QMimeData;
    mimeData->setText(items.first()->text());

    return mimeData;
}

QStringList dtkViewList::mimeTypes(void) const
{
    return QStringList() << "text/plain";
}
