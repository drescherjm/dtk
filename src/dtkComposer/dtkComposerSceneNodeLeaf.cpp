/* dtkComposerSceneNodeLeaf.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Feb  3 14:02:14 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb  6 22:06:28 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 17
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerSceneNode.h"
#include "dtkComposerSceneNode_p.h"
#include "dtkComposerSceneNodeLeaf.h"
#include "dtkComposerScenePort.h"

class dtkComposerSceneNodeLeafPrivate
{
public:
    QRectF rect;
};

dtkComposerSceneNodeLeaf::dtkComposerSceneNodeLeaf(void) : dtkComposerSceneNode(), d(new dtkComposerSceneNodeLeafPrivate)
{
    this->addInputPort(new dtkComposerScenePort(0, this));
    this->addInputPort(new dtkComposerScenePort(1, this));

    this->addOutputPort(new dtkComposerScenePort(2, this));

    d->rect = QRectF(0, 0, 150, 50);

    this->layout();
}

dtkComposerSceneNodeLeaf::~dtkComposerSceneNodeLeaf(void)
{
    delete d;

    d = NULL;
}

void dtkComposerSceneNodeLeaf::layout(void)
{
    int port_margin_top = 10;
    int port_margin_bottom = 10;
    int port_margin_left = 10;
    int port_spacing = 10;

    int node_width = d->rect.width();

    for(int i = 0; i < this->inputPorts().count(); i++)
        this->inputPorts().at(i)->setPos(QPointF(port_margin_left, i*this->inputPorts().at(i)->boundingRect().height() + i*port_spacing + port_margin_top));

    for(int i = 0; i < this->outputPorts().count(); i++)
        this->outputPorts().at(i)->setPos(QPointF(node_width - port_margin_left - this->outputPorts().at(i)->boundingRect().width(), i*this->outputPorts().at(i)->boundingRect().height() + i*port_spacing + port_margin_top));

    if(this->inputPorts().count() || this->outputPorts().count())
        if(this->inputPorts().count() >= this->outputPorts().count())
            d->rect = QRectF(d->rect.topLeft(), QSize(d->rect.width(), this->inputPorts().count() * this->inputPorts().at(0)->boundingRect().height() + port_margin_top + port_margin_bottom + (this->inputPorts().count()-1) * port_spacing));
        else
            d->rect = QRectF(d->rect.topLeft(), QSize(d->rect.width(), this->outputPorts().count() * this->outputPorts().at(0)->boundingRect().height() + port_margin_top + port_margin_bottom + (this->outputPorts().count()-1) * port_spacing));
}

QRectF dtkComposerSceneNodeLeaf::boundingRect(void) const
{
    return d->rect.adjusted(-2, -2, 2, 2);
}

void dtkComposerSceneNodeLeaf::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    static qreal radius = 5.0;

    QLinearGradient gradiant(d->rect.left(), d->rect.top(), d->rect.left(), d->rect.bottom());
    gradiant.setColorAt(0.0, QColor(Qt::white));
    gradiant.setColorAt(0.3, QColor(Qt::gray));
    gradiant.setColorAt(1.0, QColor(Qt::gray).darker());

    if (this->isSelected()) {
        painter->setPen(QPen(Qt::magenta, 2, Qt::SolidLine));
        painter->setBrush(Qt::NoBrush);
        painter->drawRoundedRect(d->rect.adjusted(-2, -2, 2, 2), radius, radius);
    }

    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine));
    painter->setBrush(gradiant);
    painter->drawRoundedRect(d->rect, radius, radius);
}
