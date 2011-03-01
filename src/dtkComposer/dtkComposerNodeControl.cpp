/* dtkComposerNodeControl.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 28 12:49:38 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 28 20:45:30 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 45
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
// dtkComposerNodeControlPrivate
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeControlPrivate
{
public:
    QList<dtkComposerEdge *> iProps(dtkComposerEdge *edge);

public:
    dtkComposerNodeProperty *property_input_condition;
};

QList<dtkComposerEdge *> dtkComposerNodeControlPrivate::iProps(dtkComposerEdge *edge)
{
    QList<dtkComposerEdge *> edges;

    if(edge->source()->node()->kind() != dtkComposerNode::Composite) {

        // qDebug() << DTK_COLOR_BG_WHITE << DTK_PRETTY_FUNCTION << edge->source()->node()->title() << "is not composite" << DTK_NO_COLOR;

        edges << edge;

    } else {

        if(edge->source()->node() == edge->destination()->node()->parentNode()) {

            // qDebug() << DTK_COLOR_BG_WHITE << DTK_PRETTY_FUNCTION << edge->source()->node()->title() << "parent is composite" << DTK_NO_COLOR;

            foreach(dtkComposerEdge *i_edge, edge->source()->node()->inputEdges())
                if(i_edge->destination() == edge->source())
                    edges << iProps(i_edge);
        } else {

            // qDebug() << DTK_COLOR_BG_WHITE << DTK_PRETTY_FUNCTION << edge->source()->node()->title() << "source is composite" << DTK_NO_COLOR;

            foreach(dtkComposerEdge *ghost, edge->source()->node()->outputGhostEdges())
                if(ghost->destination() == edge->source())
                    edges << iProps(ghost);
        }
    }

    return edges;
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

dtkComposerNodeControl::~dtkComposerNodeControl(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeControl::onInputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    qDebug() << d->iProps(edge);
}

void dtkComposerNodeControl::onOutputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    qDebug() << DTK_PRETTY_FUNCTION;
}
