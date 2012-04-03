/* dtkComposerSceneNodeLeaf.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Feb  3 14:02:14 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Mar 28 15:55:19 2012 (+0200)
 *           By: tkloczko
 *     Update #: 214
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNode.h"
#include "dtkComposerSceneNode.h"
#include "dtkComposerSceneNode_p.h"
#include "dtkComposerSceneNodeLeaf.h"
#include "dtkComposerScenePort.h"
#include "dtkComposerTransmitter.h"

class dtkComposerSceneNodeLeafPrivate
{
public:
    QRectF rect;
};

dtkComposerSceneNodeLeaf::dtkComposerSceneNodeLeaf(void) : dtkComposerSceneNode(), d(new dtkComposerSceneNodeLeafPrivate)
{
    d->rect = QRectF(0, 0, 150, 50);
}

dtkComposerSceneNodeLeaf::~dtkComposerSceneNodeLeaf(void)
{
    delete d;

    d = NULL;
}

void dtkComposerSceneNodeLeaf::wrap(dtkComposerNode *node)
{
    dtkComposerSceneNode::wrap(node);

    foreach(dtkComposerTransmitter *receiver, node->receivers()) {
        
        dtkComposerScenePort *port = new dtkComposerScenePort(dtkComposerScenePort::Input, this);
        this->addInputPort(port);
        port->setLabel(node->inputLabelHint(this->inputPorts().indexOf(port)));
        
    }

    foreach(dtkComposerTransmitter *emitter, node->emitters()) {

        dtkComposerScenePort *port = new dtkComposerScenePort(dtkComposerScenePort::Output, this);
        this->addOutputPort(port);
        port->setLabel(node->outputLabelHint(this->outputPorts().indexOf(port)));

    }

    this->layout();
}

#include "dtkComposerSceneNodeComposite.h"
#include "dtkComposerSceneNodeControl.h"

void dtkComposerSceneNodeLeaf::layout(void)
{
    int header = this->embedded() ? 0 : 15;

    int port_margin_top = 10;
    int port_margin_bottom = 10;
    int port_margin_left = 10;
    int port_spacing = 10;

// /////////////////////////////////////////////////////////////////
// Setting up port position 
// /////////////////////////////////////////////////////////////////

    for(int i = 0; i < this->inputPorts().count(); i++)
        this->inputPorts().at(i)->setPos(QPointF(port_margin_left, i*this->inputPorts().at(i)->boundingRect().height() + i*port_spacing + port_margin_top + header));

    for(int i = 0; i < this->outputPorts().count(); i++)
        this->outputPorts().at(i)->setPos(QPointF(d->rect.right() - port_margin_left - this->outputPorts().at(i)->boundingRect().width(), i*this->outputPorts().at(i)->boundingRect().height() + i*port_spacing + port_margin_top + header));

// /////////////////////////////////////////////////////////////////
// Height calculation
// /////////////////////////////////////////////////////////////////

    if(this->inputPorts().count() || this->outputPorts().count())
        if(this->inputPorts().count() >= this->outputPorts().count())
            d->rect = QRectF(d->rect.topLeft(), QSize(d->rect.width(), this->inputPorts().count() * this->inputPorts().at(0)->boundingRect().height() + port_margin_top + port_margin_bottom + (this->inputPorts().count()-1) * port_spacing + header));
        else
            d->rect = QRectF(d->rect.topLeft(), QSize(d->rect.width(), this->outputPorts().count() * this->outputPorts().at(0)->boundingRect().height() + port_margin_top + port_margin_bottom + (this->outputPorts().count()-1) * port_spacing + header));

    else if(this->embedded())
        d->rect = QRectF(d->rect.topLeft(), QSize(d->rect.width(), port_margin_top + port_margin_bottom + 10));

// /////////////////////////////////////////////////////////////////
// Redraw parent
// /////////////////////////////////////////////////////////////////

    if (dtkComposerSceneNodeComposite *parent = dynamic_cast<dtkComposerSceneNodeComposite *>(this->parent())) {
        if(!parent->root()) {
            if (parent->entered() || (parent->flattened() && !parent->embedded())) {
                parent->layout();
            }
        }
    }
    
// /////////////////////////////////////////////////////////////////
// Update edges geometry
// /////////////////////////////////////////////////////////////////

    QRectF updateRect;
    
    foreach(dtkComposerSceneEdge *edge, this->inputEdges()) {
        edge->adjust();
        updateRect |= edge->boundingRect();
    }
    
    foreach(dtkComposerSceneEdge *edge, this->outputEdges()) {
        edge->adjust();
        updateRect |= edge->boundingRect();
    }
    
    this->update(updateRect);
}

void dtkComposerSceneNodeLeaf::resize(qreal width, qreal height)
{
    d->rect = QRectF(d->rect.topLeft(), QSizeF(width, height));
}

QRectF dtkComposerSceneNodeLeaf::boundingRect(void) const
{
    return d->rect.adjusted(-2, -2, 2, 2);
}

void dtkComposerSceneNodeLeaf::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    qreal radius = this->embedded() ? 0.0 : 5.0;

    if (this->isSelected()) {
        painter->setPen(QPen(Qt::magenta, 2, Qt::SolidLine));
        painter->setBrush(Qt::NoBrush);
        painter->drawRoundedRect(d->rect.adjusted(-2, -2, 2, 2), radius, radius);
    }

    if(this->embedded())
        painter->setPen(Qt::NoPen);
    else
        painter->setPen(QPen(Qt::black, 1, Qt::SolidLine));

    QLinearGradient gradiant(d->rect.left(), d->rect.top(), d->rect.left(), d->rect.bottom());
    gradiant.setColorAt(0.0, QColor(Qt::white));
    gradiant.setColorAt(0.3, QColor(Qt::gray));
    gradiant.setColorAt(1.0, QColor(Qt::gray).darker());

    painter->setBrush(gradiant);

    painter->drawRoundedRect(d->rect, radius, radius);

    // Drawing node's title

    qreal margin = 5.0;

    QFont font = painter->font();
    QFontMetricsF metrics(font);
    QString title_text = metrics.elidedText(this->title(), Qt::ElideMiddle, this->boundingRect().width()-2-4*margin);
    QRectF title_rect = metrics.boundingRect(title_text);

    QPointF title_pos;

    if(!this->embedded())
        title_pos = QPointF(2*margin, 2*margin + metrics.xHeight());
    else
        title_pos = QPointF(d->rect.right() - 2*margin - metrics.width(title_text), 2*margin + metrics.xHeight());

    painter->setPen(QPen(QColor(Qt::gray).darker()));
    painter->drawText(title_pos + QPointF(0, -1), title_text);
    painter->setPen(QPen(QColor(Qt::gray)));
    painter->drawText(title_pos + QPointF(0, 1), title_text);
    painter->setPen(QPen(QColor(Qt::white)));
    painter->drawText(title_pos, title_text);
}
