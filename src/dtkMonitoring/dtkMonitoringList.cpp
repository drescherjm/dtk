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

#include "dtkMonitoringModel.h"
#include "dtkMonitoringList.h"
#include <dtkComposer/dtkComposerNodeMetaData.h>
#include <QStyledItemDelegate>

class dtkMonitoringListItemDelegate: public QStyledItemDelegate
{
public:
    dtkMonitoringListItemDelegate(dtkMonitoringModel *model);

public:
    virtual void paint(QPainter *painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;

public:
    virtual QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const;

protected:
    dtkMonitoringModel *m_model;
};



class dtkMonitoringListPrivate
{
public:

};

dtkMonitoringList::dtkMonitoringList(QWidget *parent) : QListView(parent)
{
    d = new dtkMonitoringListPrivate;

    this->setAttribute(Qt::WA_MacShowFocusRect, false);
    this->setFrameShape(QFrame::NoFrame);
}

dtkMonitoringList::~dtkMonitoringList(void)
{
    delete d;
}

void dtkMonitoringList::setModel(dtkMonitoringModel *model)
{
    setItemDelegate(new dtkMonitoringListItemDelegate(model));
    QListView::setModel(model);
}

dtkMonitoringListItemDelegate::dtkMonitoringListItemDelegate(dtkMonitoringModel *model): m_model(model)
{
    m_model=model;
}



void dtkMonitoringListItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QVariant variant=(m_model->data(index,Qt::DisplayRole));
    dtkComposerNode* item=NULL;
    if (variant.canConvert<dtkComposerNode*>())
        item = variant.value<dtkComposerNode*>();

    if(!item)
        return;

    QLinearGradient gradiant(option.rect.left(), option.rect.top(), option.rect.left(), option.rect.bottom());
    qreal stripe = 10. / option.rect.height();
    QString kindText;

    switch(item->nodeMetaData()->kind())
    {
    case dtkComposerNode::Process:
        gradiant.setColorAt(0.0, QColor(Qt::red).lighter());
        gradiant.setColorAt(stripe, QColor(Qt::darkRed));
        gradiant.setColorAt(1.0, QColor(Qt::darkRed).darker());
        kindText="process";
        break;

    case dtkComposerNode::Data:
        gradiant.setColorAt(0.0, QColor(Qt::blue).lighter());
        gradiant.setColorAt(stripe, QColor(Qt::darkBlue));
        gradiant.setColorAt(1.0, QColor(Qt::darkBlue).darker());
        kindText="data";
        break;

    case dtkComposerNode::View:
        gradiant.setColorAt(0.0, QColor(Qt::green).lighter());
        gradiant.setColorAt(stripe, QColor(Qt::darkGreen));
        gradiant.setColorAt(1.0, QColor(Qt::darkGreen).darker());
        kindText="view";
        break;

    case dtkComposerNode::Actor:
        gradiant.setColorAt(0.0, QColor(255, 175, 0).lighter());
        gradiant.setColorAt(stripe, QColor(155, 75, 0));
        gradiant.setColorAt(1.0, QColor(155, 75, 0).darker());
        kindText="actor";
        break;

    default:
        gradiant.setColorAt(0.0, QColor(Qt::gray).lighter());
        gradiant.setColorAt(stripe, QColor(Qt::darkGray));
        gradiant.setColorAt(1.0, QColor(Qt::darkGray).darker());
        kindText="unknown";
        break;
    }

    painter->fillRect(option.rect, gradiant);

    painter->setPen(Qt::white);
    painter->drawLine(option.rect.topLeft() + QPoint(0, 1), option.rect.topRight() + QPoint(0, 1));

    static int m  =  5;
    static int h1 = 20;
    static int h2 = 20;
    static int h3 = 20;

    int w = option.rect.width();
    int h = option.rect.height();
    int t = option.rect.top();
    int r = option.rect.right();

    QRect title_rect = QRect(m, t+1*m,       w-2*m, h1);
    QRect type_rect = QRect(m, t+3*m+h1, w-2*m, h3);

    painter->setPen(Qt::white);
    painter->drawText(title_rect, Qt::AlignCenter | Qt::AlignTop, item->titleHint());

    painter->setPen(QColor(Qt::lightGray));
    painter->drawText(type_rect, Qt::AlignLeft | Qt::AlignTop, kindText+": "+item->type());
}

QSize dtkMonitoringListItemDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    return QSize(100, 80);
}


//
// dtkMonitoringList.cpp ends here
