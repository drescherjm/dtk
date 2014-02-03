/* dtkViewList.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed May 16 09:39:06 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Jan 21 17:47:59 2014 (+0100)
 *           By: Selim Kraria
 *     Update #: 48
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

    //connect(dtkAbstractViewFactory::instance(), SIGNAL(nameChanged(dtkAbstractView *, const QString&)), this, SLOT(update()));

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

    foreach(QString objectName, dtkAbstractViewFactory::instance()->viewNames()) {
        dtkAbstractView *view = dtkAbstractViewFactory::instance()->view(objectName);
        QListWidgetItem *item = new QListWidgetItem;
        QString text = objectName;
        if (!view->name().isEmpty())
            text += " - " + view->name();
        item->setText(text);
        this->addItem(item);

        connect(view, SIGNAL(nameChanged()), this, SLOT(update()));
    }
}

void dtkViewList::clear(void)
{
    QListWidget::clear();
}

QMimeData *dtkViewList::mimeData(const QList<QListWidgetItem *> items) const
{
    QMimeData *mimeData = new QMimeData;
    mimeData->setText(items.first()->text().split(" ").first());

    return mimeData;
}

QStringList dtkViewList::mimeTypes(void) const
{
    return QStringList() << "text/plain";
}
