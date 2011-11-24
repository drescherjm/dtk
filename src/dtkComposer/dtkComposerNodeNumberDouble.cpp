/* dtkComposerNodeNumberDouble.cpp --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: jeu. nov. 17 22:13:04 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Nov 21 09:52:03 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 8
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

    this->setGenre(QVariant::Double);
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

//! Updates the graphical aspect of the node.
/*! 
 *  
 */
void dtkComposerNodeNumberDouble::touch(void)
{
    if (!this->isInteractive())
        this->setEditorText(QString::number(d->receiver->data()));

    dtkComposerNodeNumber::touch();
}

//! 
/*! 
 *  Reimplemented from dtkComposerNode.
 */
void dtkComposerNodeNumberDouble::pull(dtkComposerEdge *route, dtkComposerNodeProperty *property)
{
    Q_UNUSED(route);
    Q_UNUSED(property);
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
void dtkComposerNodeNumberDouble::push(dtkComposerEdge *route, dtkComposerNodeProperty *property)
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
bool dtkComposerNodeNumberDouble::onLeftRouteConnected(dtkComposerEdge *route, dtkComposerNodeProperty *destination)
{
    Q_UNUSED(destination);

    if (!(d->receiver = dynamic_cast<dtkComposerNodeTransmitter<double> *> (route->source()->node()->emitter(route->source()))))
        return false;

    this->interactiveOff();

    return true;
}

//! 
/*! 
 *  Reimplemented from dtkComposerNode.
 */
bool dtkComposerNodeNumberDouble::onRightRouteConnected(dtkComposerEdge *route, dtkComposerNodeProperty *property)
{
    return true;
}
