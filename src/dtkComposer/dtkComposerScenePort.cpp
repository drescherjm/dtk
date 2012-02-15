/* dtkComposerScenePort.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Feb  3 13:59:41 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Feb 15 18:15:28 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 78
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerSceneNode.h"
#include "dtkComposerScenePort.h"

class dtkComposerScenePortPrivate
{
public:
    unsigned int id;

public:
    dtkComposerScenePort::Type type;

public:
    dtkComposerSceneNode *node;

public:
    QGraphicsEllipseItem *ellipse;
    QGraphicsTextItem *label;
};

dtkComposerScenePort::dtkComposerScenePort(unsigned int id, Type type, dtkComposerSceneNode *parent) : QGraphicsItem(parent), d(new dtkComposerScenePortPrivate)
{
    d->id = id;
    d->type = type;
    d->node = parent;

    d->ellipse = new QGraphicsEllipseItem(this);
    d->ellipse->setPen(QPen(Qt::darkGray, 1));
    d->ellipse->setBrush(Qt::lightGray);
    d->ellipse->setRect(0, 0, 10, 10);

    d->label = new QGraphicsTextItem(this);
#if defined(Q_WS_MAC)
    d->label->setFont(QFont("Lucida Grande", 11));
#else
    d->label->setFont(QFont("Lucida Grande", 9));
#endif
    d->label->setDefaultTextColor(Qt::white);
    
    this->setFlags(QGraphicsItem::ItemIsSelectable);

    this->setZValue(1);
}

dtkComposerScenePort::~dtkComposerScenePort(void)
{
    delete d;

    d = NULL;
}

unsigned int dtkComposerScenePort::id(void) const
{
    return d->id;
}

dtkComposerScenePort::Type dtkComposerScenePort::type(void)
{
    return d->type;
}

dtkComposerSceneNode *dtkComposerScenePort::node(void)
{
    return d->node;
}

void dtkComposerScenePort::setLabel(const QString& label)
{
    d->label->setPlainText(label);
    
    QFontMetricsF fm(d->label->font());

    if(d->type == Input)
        d->label->setPos(d->ellipse->pos() + QPointF(d->ellipse->boundingRect().width(), 0) - QPointF(0, fm.height()/2.0));
    else
        d->label->setPos(d->ellipse->pos() - QPointF(7, 0) - QPointF(fm.width(label), fm.height()/2.0));

}

QRectF dtkComposerScenePort::boundingRect(void) const
{
    return QRectF(0, 0, 10, 10);
}

void dtkComposerScenePort::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
