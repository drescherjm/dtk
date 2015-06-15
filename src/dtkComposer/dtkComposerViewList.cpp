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

#include "dtkComposerViewController.h"
#include "dtkComposerViewList.h"

class dtkComposerViewListPrivate
{
public:
    QList<QWidget *> connected_views;
};

dtkComposerViewList::dtkComposerViewList(QWidget *parent) : QListWidget(parent), d(new dtkComposerViewListPrivate)
{
    this->setAttribute(Qt::WA_MacShowFocusRect, false);
    this->setDragEnabled(true);
    this->setFrameStyle(QFrame::NoFrame);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    this->setFixedHeight(100);

    connect(dtkComposerViewController::instance(), SIGNAL(inserted(QWidget *, const QString&)), this, SLOT(update()));

    this->update();
}

dtkComposerViewList::~dtkComposerViewList(void)
{
    delete d;

    d = NULL;
};

void dtkComposerViewList::update(void)
{
    this->clear();

    foreach(QString objectName, dtkComposerViewController::instance()->viewNames()) {
        QWidget *view = dtkComposerViewController::instance()->view(objectName);
        QListWidgetItem *item = new QListWidgetItem;
        QString text = objectName;
        item->setText(text);
        this->addItem(item);

        if(!d->connected_views.contains(view)) {
            d->connected_views.append(view);
        }
    }
}

void dtkComposerViewList::clear(void)
{
    QListWidget::clear();
}

QMimeData *dtkComposerViewList::mimeData(const QList<QListWidgetItem *> items) const
{
    QMimeData *mimeData = new QMimeData;
    mimeData->setText(items.first()->text().split(" ").first());

    return mimeData;
}

QStringList dtkComposerViewList::mimeTypes(void) const
{
    return QStringList() << "text/plain";
}

//
// dtkComposerViewList.cpp ends here
