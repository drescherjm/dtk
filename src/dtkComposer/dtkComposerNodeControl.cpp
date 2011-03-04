/* dtkComposerNodeControl.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 28 12:49:38 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Mar  4 12:41:03 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 166
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerEdge.h"
#include "dtkComposerNodeControl.h"
#include "dtkComposerNodeControlBlock.h"
#include "dtkComposerNodeProperty.h"

#include <dtkCore/dtkGlobal.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlPrivate
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeControlPrivate
{
public:
    QList<dtkComposerNodeProperty *> iProps(dtkComposerEdge *edge);

public:
    QList<dtkComposerNodeControlBlock *> blocks;

public:
    dtkComposerNodeProperty *property_input_condition;
};

QList<dtkComposerNodeProperty *> dtkComposerNodeControlPrivate::iProps(dtkComposerEdge *edge)
{
    QList<dtkComposerNodeProperty *> properties;

    return properties;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControl
// /////////////////////////////////////////////////////////////////

dtkComposerNodeControl::dtkComposerNodeControl(dtkComposerNode *parent) : dtkComposerNode(parent), d(new dtkComposerNodeControlPrivate)
{
    d->property_input_condition = new dtkComposerNodeProperty("condition", dtkComposerNodeProperty::Input, dtkComposerNodeProperty::Multiple, this);
    d->property_input_condition->setRect(QRectF(this->boundingRect().left() + 5, this->boundingRect().top() + 5, 10, 10));
    d->property_input_condition->setPos(QPointF(d->property_input_condition->pos().x(), this->boundingRect().top()));

    this->addInputProperty(d->property_input_condition);

    this->setAcceptHoverEvents(true);
    this->setKind(dtkComposerNode::Control);
    this->setResizable(true);
    this->setZValue(-2000);
    this->setSize(400, 400);
}

dtkComposerNodeControl::~dtkComposerNodeControl(void)
{
    delete d;

    d = NULL;
}

dtkComposerNodeControlBlock *dtkComposerNodeControl::addBlock(const QString& title)
{
    dtkComposerNodeControlBlock *block = new dtkComposerNodeControlBlock(title, this);
    
    d->blocks << block;

    this->layout();

    return block;
}

QList<dtkComposerNodeControlBlock *> dtkComposerNodeControl::blocks(void)
{
    return d->blocks;
}

void dtkComposerNodeControl::layout(void)
{
    dtkComposerNode::layout();

    for(int i = 0; i < d->blocks.count(); i++)
        d->blocks.at(i)->setRect(QRectF(this->boundingRect().x(),
                                       this->boundingRect().y() + 23 + i * ((this->boundingRect().height() - 46) / d->blocks.count()),
                                       this->boundingRect().width(),
                                       (this->boundingRect().height() - 46) / d->blocks.count()));
}

void dtkComposerNodeControl::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    dtkComposerNode::paint(painter, option, widget);
}

void dtkComposerNodeControl::onInputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    // qDebug() << DTK_PRETTY_FUNCTION;
}

void dtkComposerNodeControl::onOutputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    // qDebug() << DTK_PRETTY_FUNCTION;
}

bool dtkComposerNodeControl::condition(void)
{
    bool value = false;

    if(!d->property_input_condition)
        return value;

    if(!d->property_input_condition->edge())
        return value;

    QVariant p_value = d->property_input_condition->edge()->source()->node()->value(d->property_input_condition->edge()->source());

    if(!p_value.canConvert(QVariant::Bool))
        return value;
    else
        value = p_value.toBool();

    return value;
}
