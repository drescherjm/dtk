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

#include "dtkWidgetsViewController.h"
#include "dtkWidgetsViewList.h"

class dtkWidgetsViewListPrivate
{
public:
    QList<QWidget *> connected_views;
};

dtkWidgetsViewList::dtkWidgetsViewList(QWidget *parent) : QListWidget(parent), d(new dtkWidgetsViewListPrivate)
{
    this->setAttribute(Qt::WA_MacShowFocusRect, false);
    this->setDragEnabled(true);
    this->setFrameStyle(QFrame::NoFrame);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    this->setFixedHeight(100);

    connect(dtkWidgetsViewController::instance(), SIGNAL(inserted(QWidget *, const QString&)), this, SLOT(update()));

    this->update();
}

dtkWidgetsViewList::~dtkWidgetsViewList(void)
{
    delete d;

    d = NULL;
};

void dtkWidgetsViewList::update(void)
{
    this->clear();

    foreach(QString objectName, dtkWidgetsViewController::instance()->viewNames()) {
        QWidget *view = dtkWidgetsViewController::instance()->view(objectName);
        QListWidgetItem *item = new QListWidgetItem;
        QString text = objectName;
        item->setText(text);
        this->addItem(item);

        if(!d->connected_views.contains(view)) {
            d->connected_views.append(view);
        }
    }
}

void dtkWidgetsViewList::clear(void)
{
    QListWidget::clear();
}

QMimeData *dtkWidgetsViewList::mimeData(const QList<QListWidgetItem *> items) const
{
    QMimeData *mimeData = new QMimeData;
    mimeData->setText(items.first()->text().split(" ").first());

    return mimeData;
}

QStringList dtkWidgetsViewList::mimeTypes(void) const
{
    return QStringList() << "text/plain";
}

//
// dtkWidgetsViewList.cpp ends here
