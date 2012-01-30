/* dtkComposerNodeNumberDouble.cpp --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: jeu. nov. 17 22:13:04 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Dec  7 16:06:53 2011 (+0100)
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
#include "dtkComposerNodeNumberDouble.h"
#include "dtkComposerNodeProperty.h"
#include "dtkComposerNodeTransmitter.h"
#include "dtkComposerRoute.h"

#include <dtkCore/dtkGlobal.h>
 
// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberDoublePrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeNumberDoublePrivate
{
public:
    dtkComposerNodeProperty *property_left_value;
    dtkComposerNodeProperty *property_right_value;

public:
    dtkComposerNodeTransmitter<double> *emitter;
    dtkComposerNodeTransmitter<double> *receiver;

public:
    QHash<dtkComposerRoute *, dtkComposerNodeTransmitter<double> *> receivers;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeString implementation
// /////////////////////////////////////////////////////////////////

//! Constructs double number node.
/*! 
 *  
 */
dtkComposerNodeNumberDouble::dtkComposerNodeNumberDouble(dtkComposerNode *parent) : dtkComposerNodeNumber(parent), d(new dtkComposerNodeNumberDoublePrivate)
{
    d->property_left_value = new dtkComposerNodeProperty("value", dtkComposerNodeProperty::Left, dtkComposerNodeProperty::AsInput, dtkComposerNodeProperty::Multiple, this);
    d->property_right_value = new dtkComposerNodeProperty("value", dtkComposerNodeProperty::Right, dtkComposerNodeProperty::AsOutput, dtkComposerNodeProperty::Multiple, this);

    this->setTitle("Number");
    this->setKind(dtkComposerNode::Atomic);
    this->setType("dtkComposerNumberDouble");

    this->setLabelText("DOUBLE");

    this->g->appendLeftProperty(d->property_left_value);
    this->g->appendRightProperty(d->property_right_value);

    d->emitter = new dtkComposerNodeTransmitter<double>();
    d->receiver = NULL;
}

//! Destroys double number node.
/*! 
 *  
 */
dtkComposerNodeNumberDouble::~dtkComposerNodeNumberDouble(void)
{
    delete d;

    d = NULL;
}

//! Returns number type using QVariant flags.
/*! 
 *  
 */
const QVariant::Type dtkComposerNodeNumberDouble::genre(void) const
{
    return QVariant::Double;
}

//! Updates the graphical aspect of the node.
/*! 
 *  
 */
void dtkComposerNodeNumberDouble::touch(void)
{   
    if(!this->isInteractive())
        this->setEditorText(QString::number(d->receiver->data()));

    dtkComposerNode::touch();
}

//! 
/*! 
 *  Reimplemented from dtkComposerNode.
 */
void dtkComposerNodeNumberDouble::pull(dtkComposerRoute *route, dtkComposerNodeProperty *property)
{
    Q_UNUSED(property);

    d->receiver = d->receivers.value(route);
}

//! 
/*! 
 *  Reimplemented from dtkComposerNode.
 */
void dtkComposerNodeNumberDouble::run(void)
{
    if (this->isInteractive())
        d->emitter->setData(this->editorText().toDouble());
    else
        d->emitter->setData(d->receiver->data());
}

//! 
/*! 
 *  Reimplemented from dtkComposerNode.
 */
void dtkComposerNodeNumberDouble::push(dtkComposerRoute *route, dtkComposerNodeProperty *property)
{
    Q_UNUSED(route);
    Q_UNUSED(property);
}

//! 
/*! 
 *  Reimplemented from dtkComposerNode.
 */
dtkComposerNodeAbstractTransmitter *dtkComposerNodeNumberDouble::emitter(dtkComposerNodeProperty *property)
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
bool dtkComposerNodeNumberDouble::onLeftRouteConnected(dtkComposerRoute *route, dtkComposerNodeProperty *destination)
{
    Q_UNUSED(destination);

    if (!(d->receiver = dynamic_cast<dtkComposerNodeTransmitter<double> *>(route->source()->node()->emitter(route->source()))))
        return false;

    d->receivers.insert(route, static_cast<dtkComposerNodeTransmitter<double> *>(route->source()->node()->emitter(route->source())));

    if (d->receivers.count() == 1)
        d->receiver = d->receivers.values().first();

    this->interactiveOff();

    return true;
}

//! 
/*! 
 *  Reimplemented from dtkComposerNode.
 */
bool dtkComposerNodeNumberDouble::onRightRouteConnected(dtkComposerRoute *route, dtkComposerNodeProperty *property)
{
    return true;
}
