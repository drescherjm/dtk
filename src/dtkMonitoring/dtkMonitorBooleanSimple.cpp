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

#include "dtkMonitorBoolean.h"
#include "dtkMonitorBooleanSimple.h"

#include <dtkComposer/dtkComposerNodeBoolean>

#include <QGraphicsPixmapItem>

class dtkMonitorBooleanSimplePrivate
{
public:
    QGraphicsPixmapItem *pixmap_on;
    QGraphicsPixmapItem *pixmap_off;
};

dtkMonitorBooleanSimple::dtkMonitorBooleanSimple(QGraphicsItem *parent) : dtkMonitorBoolean(parent)
{
    d = new dtkMonitorBooleanSimplePrivate;

    d->pixmap_on  = new QGraphicsPixmapItem(this);
    d->pixmap_off = new QGraphicsPixmapItem(this);

    d->pixmap_on->setPixmap(QPixmap("qrc:dtkMonitoring/pixmaps/dtk-monitor-boolean-simple-on.png"));
    d->pixmap_off->setPixmap(QPixmap("qrc:dtkMonitoring/pixmaps/dtk-monitor-boolean-simple-off.png"));
}

dtkMonitorBooleanSimple::~dtkMonitorBooleanSimple(void)
{
    delete d;
}

void dtkMonitorBooleanSimple::setNode(dtkComposerNode *node)
{
    dtkMonitor::setNode(node);

    d->pixmap_on->setVisible(  dynamic_cast<dtkComposerNodeBoolean *>(node)->value());
    d->pixmap_off->setVisible(!dynamic_cast<dtkComposerNodeBoolean *>(node)->value());

}

QRectF dtkMonitorBooleanSimple::boundingRect(void) const
{
    return d->pixmap_on->boundingRect();
}

void dtkMonitorBooleanSimple::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
}

//
// dtkMonitorBooleanSimple.cpp ends here
