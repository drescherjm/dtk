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

#include "dtkMonitorReal.h"
#include "dtkMonitorRealSimple.h"

#include <dtkComposer/dtkComposerNodeReal>

#include <QGraphicsPixmapItem>
#include <QFocusEvent>

class dtkMonitorRealSimplePrivate
{
public:
    //QGraphicsPixmapItem *wrapper;
    QGraphicsProxyWidget *spinBoxProxy;
};

dtkMonitorRealSimple::dtkMonitorRealSimple(QGraphicsItem *parent) : dtkMonitorReal(parent)
{
    setFlag(QGraphicsItem::ItemIsFocusable);
    d = new dtkMonitorRealSimplePrivate;
    //d->wrapper  = new QGraphicsPixmapItem(this);
    //d->wrapper->setPixmap(QPixmap(":dtkMonitoring/pixmaps/dtk-monitor-Real-simple-wrapper.png"));

    d->spinBoxProxy = new QGraphicsProxyWidget(this);
    d->spinBoxProxy->setFlag(QGraphicsItem::ItemIsFocusable,false);
    QDoubleSpinBox* spinBox=new QDoubleSpinBox();
    spinBox->setWindowFlags(Qt::Window);
    //spinBox->setFocusPolicy(Qt::StrongFocus);
    d->spinBoxProxy->setWidget(spinBox);
    d->spinBoxProxy->setFocusPolicy(Qt::StrongFocus);
    spinBox->setVisible(true);
}

dtkMonitorRealSimple::~dtkMonitorRealSimple(void)
{
    delete d;
}

void dtkMonitorRealSimple::setNode(dtkComposerNode *node)
{
    dtkMonitor::setNode(node);
    d->spinBoxProxy->setVisible(true);
}

QRectF dtkMonitorRealSimple::boundingRect(void) const
{
    return d->spinBoxProxy->boundingRect().adjusted(-2,-2,2,2);
}

void dtkMonitorRealSimple::focusInEvent(QFocusEvent * event)
{
    qDebug()<<Q_FUNC_INFO;
    d->spinBoxProxy->widget()->setFocus();
}

//
// dtkMonitorRealSimple.cpp ends here
