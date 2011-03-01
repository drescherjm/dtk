/* dtkComposerNodeControl.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 28 12:49:38 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Mar  1 18:32:51 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 78
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerEdge.h"
#include "dtkComposerNodeControl.h"
#include "dtkComposerNodeProperty.h"

#include <dtkCore/dtkGlobal.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlBloc
// /////////////////////////////////////////////////////////////////

dtkComposerNodeControlBloc::dtkComposerNodeControlBloc(QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
    QPen pen;
    pen.setColor(QColor("#c7c7c7"));
    pen.setStyle(Qt::DashLine);
    pen.setWidth(1);

    this->setPen(pen);
    this->setBrush(Qt::NoBrush);
}

dtkComposerNodeControlBloc::~dtkComposerNodeControlBloc(void)
{

}

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlPrivate
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeControlPrivate
{
public:
    QList<dtkComposerNodeProperty *> iProps(dtkComposerEdge *edge);

public:
    QList<dtkComposerNodeControlBloc *> blocs;

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

    this->setKind(dtkComposerNode::Control);
    this->setResizable(true);
    this->setZValue(5);
}

dtkComposerNodeControlBloc *dtkComposerNodeControl::addBlock(void)
{
    dtkComposerNodeControlBloc *bloc = new dtkComposerNodeControlBloc(this);
    
    d->blocs << bloc;

    return bloc;
}

dtkComposerNodeControl::~dtkComposerNodeControl(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeControl::layout(void)
{
    dtkComposerNode::layout();

    for(int i = 0; i < d->blocs.count(); i++)
        d->blocs.at(i)->setRect(QRectF(this->boundingRect().x(),
                                       this->boundingRect().y() + 23 + i * (this->boundingRect().height() - 46 / d->blocs.count()),
                                       this->boundingRect().width(),
                                       this->boundingRect().height() - 46 / d->blocs.count()));
}

void dtkComposerNodeControl::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    dtkComposerNode::paint(painter, option, widget);
}

void dtkComposerNodeControl::onInputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    qDebug() << DTK_PRETTY_FUNCTION;
}

void dtkComposerNodeControl::onOutputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    qDebug() << DTK_PRETTY_FUNCTION;
}
