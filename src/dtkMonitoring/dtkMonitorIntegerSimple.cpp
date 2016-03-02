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

#include "dtkMonitorInteger.h"
#include "dtkMonitorIntegerSimple.h"

#include <dtkComposer/dtkComposerNodeInteger>

#include <QGraphicsPixmapItem>
#include <QFocusEvent>

class dtkMonitorIntegerSimplePrivate
{
public:
    //QGraphicsPixmapItem *wrapper;
    QGraphicsProxyWidget *spinBoxProxy;
};

dtkMonitorIntegerSimple::dtkMonitorIntegerSimple(QGraphicsItem *parent) : dtkMonitorInteger(parent)
{
    setFlag(QGraphicsItem::ItemIsFocusable);
    d = new dtkMonitorIntegerSimplePrivate;
    //d->wrapper  = new QGraphicsPixmapItem(this);
    //d->wrapper->setPixmap(QPixmap(":dtkMonitoring/pixmaps/dtk-monitor-Integer-simple-wrapper.png"));

    d->spinBoxProxy = new QGraphicsProxyWidget(this);
    d->spinBoxProxy->setFlag(QGraphicsItem::ItemIsFocusable,false);
    QSpinBox* spinBox=new QSpinBox();
    spinBox->setWindowFlags(Qt::Window);
    d->spinBoxProxy->setWidget(spinBox);
    d->spinBoxProxy->setFocusPolicy(Qt::StrongFocus);
    spinBox->setVisible(true);
}

dtkMonitorIntegerSimple::~dtkMonitorIntegerSimple(void)
{
    delete d;
}

void dtkMonitorIntegerSimple::setNode(dtkComposerNode *node)
{
    dtkMonitor::setNode(node);
    d->spinBoxProxy->setVisible(true);
}

QRectF dtkMonitorIntegerSimple::boundingRect(void) const
{
    return d->spinBoxProxy->boundingRect().adjusted(-2,-2,2,2);
}

//
// dtkMonitorIntegerSimple.cpp ends here
