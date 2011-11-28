/* dtkComposerNodeNumberInteger.cpp --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: jeu. nov. 17 20:50:45 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Nov 28 14:33:34 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 35
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerEdge.h"
#include "dtkComposerNodeNumberInteger.h"
#include "dtkComposerNodeProperty.h"
#include "dtkComposerNodeTransmitter.h"

#include <dtkCore/dtkGlobal.h>
 
// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberIntegerPrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeNumberIntegerPrivate
{
public:
    dtkComposerNodeProperty *property_left_value;
    dtkComposerNodeProperty *property_right_value;

public:
    dtkComposerNodeTransmitter<int> *emitter;
    dtkComposerNodeTransmitter<int> *receiver;

public:
    QHash<dtkComposerEdge *, dtkComposerNodeTransmitter<int> *> receivers;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeString implementation
// /////////////////////////////////////////////////////////////////

//! Constructs integer number node.
/*! 
 *  
 */
dtkComposerNodeNumberInteger::dtkComposerNodeNumberInteger(dtkComposerNode *parent) : dtkComposerNodeNumber(parent), d(new dtkComposerNodeNumberIntegerPrivate)
{
    d->property_left_value = new dtkComposerNodeProperty("value", dtkComposerNodeProperty::Left, dtkComposerNodeProperty::AsInput, dtkComposerNodeProperty::Multiple, this);
    d->property_right_value = new dtkComposerNodeProperty("value", dtkComposerNodeProperty::Right, dtkComposerNodeProperty::AsOutput, dtkComposerNodeProperty::Multiple, this);

    this->setTitle("Number");
    this->setKind(dtkComposerNode::Atomic);
    this->setType("dtkComposerNumberInteger");

    this->setLabelText("INT");

    this->g->appendLeftProperty(d->property_left_value);
    this->g->appendRightProperty(d->property_right_value);

    d->emitter = new dtkComposerNodeTransmitter<int>();
    d->receiver = NULL;
}

//! Destroys integer number node.
/*! 
 *  
 */
dtkComposerNodeNumberInteger::~dtkComposerNodeNumberInteger(void)
{
    delete d;

    d = NULL;
}

//! Returns number type using QVariant flags.
/*! 
 *  
 */
const QVariant::Type dtkComposerNodeNumberInteger::genre(void) const
{
    return QVariant::Int;
}

//! Updates the graphical aspect of the node.
/*! 
 *  
 */
void dtkComposerNodeNumberInteger::touch(void)
{
    if (!this->isInteractive())
        this->setEditorText(QString::number(d->receiver->data()));

    dtkComposerNode::touch();
}

//! 
/*! 
 *  Reimplemented from dtkComposerNode.
 */
void dtkComposerNodeNumberInteger::pull(dtkComposerEdge *route, dtkComposerNodeProperty *property)
{
    Q_UNUSED(property);

    d->receiver = d->receivers.value(route);
}

//! 
/*! 
 *  Reimplemented from dtkComposerNode.
 */
void dtkComposerNodeNumberInteger::run(void)
{
    if (this->isInteractive())
        d->emitter->setData(this->editorText().toInt());
    else
        d->emitter->setData(d->receiver->data());
}

//! 
/*! 
 *  Reimplemented from dtkComposerNode.
 */
void dtkComposerNodeNumberInteger::push(dtkComposerEdge *route, dtkComposerNodeProperty *property)
{
    Q_UNUSED(route);
    Q_UNUSED(property);
}

//! 
/*! 
 *  Reimplemented from dtkComposerNode.
 */
dtkComposerNodeAbstractTransmitter *dtkComposerNodeNumberInteger::emitter(dtkComposerNodeProperty *property)
{
    if (property == d->property_right_value)
        return d->emitter;
    
    return NULL;
}

//! Sets the receiver from the emitter of the node at the source of \a
//! route.
/*! 
 *  When the source emitter can be casted into current receiver type,
 *  true is returned. Else it returns false.
 *
 *  It makes also the node non-interactive nad clears the text of
 *  edition aera.
 *
 *  Reimplemented from dtkComposerNode.
 */
bool dtkComposerNodeNumberInteger::onLeftRouteConnected(dtkComposerEdge *route, dtkComposerNodeProperty *destination)
{
    Q_UNUSED(destination);

    if (!(d->receiver = dynamic_cast<dtkComposerNodeTransmitter<int> *>(route->source()->node()->emitter(route->source()))))
        return false;

    d->receivers.insert(route, static_cast<dtkComposerNodeTransmitter<int> *>(route->source()->node()->emitter(route->source())));

    if (d->receivers.count() == 1)
        d->receiver = d->receivers.values().first();

    this->interactiveOff();

    return true;
}

//! 
/*! 
 *  Reimplemented from dtkComposerNode.
 */
bool dtkComposerNodeNumberInteger::onRightRouteConnected(dtkComposerEdge *route, dtkComposerNodeProperty *property)
{
    return true;
}
