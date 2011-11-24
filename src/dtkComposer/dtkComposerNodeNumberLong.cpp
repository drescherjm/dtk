/* dtkComposerNodeNumberLong.cpp --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: jeu. nov. 17 21:55:21 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Nov 21 09:51:50 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 16
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerEdge.h"
#include "dtkComposerNodeNumberLong.h"
#include "dtkComposerNodeProperty.h"
#include "dtkComposerNodeTransmitter.h"

#include <dtkCore/dtkGlobal.h>
 
// /////////////////////////////////////////////////////////////////
// dtkComposerNodeNumberLongPrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeNumberLongPrivate
{
public:
    dtkComposerNodeProperty *property_left_value;
    dtkComposerNodeProperty *property_right_value;

public:
    dtkComposerNodeTransmitter<qlonglong> *emitter;
    dtkComposerNodeTransmitter<qlonglong> *receiver;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeString implementation
// /////////////////////////////////////////////////////////////////

//! Constructs long integer number node.
/*! 
 *  
 */
dtkComposerNodeNumberLong::dtkComposerNodeNumberLong(dtkComposerNode *parent) : dtkComposerNodeNumber(parent), d(new dtkComposerNodeNumberLongPrivate)
{
    d->property_left_value = new dtkComposerNodeProperty("value", dtkComposerNodeProperty::Left, dtkComposerNodeProperty::AsInput, dtkComposerNodeProperty::Multiple, this);
    d->property_right_value = new dtkComposerNodeProperty("value", dtkComposerNodeProperty::Right, dtkComposerNodeProperty::AsOutput, dtkComposerNodeProperty::Multiple, this);

    this->setTitle("Number");
    this->setKind(dtkComposerNode::Atomic);
    this->setType("dtkComposerNumberLong");

    this->setLabelText("LONG");

    this->g->appendLeftProperty(d->property_left_value);
    this->g->appendRightProperty(d->property_right_value);

    d->emitter = new dtkComposerNodeTransmitter<qlonglong>();
    d->receiver = NULL;

    this->setGenre(QVariant::LongLong);
}

//! Destroys long integer number node.
/*! 
 *  
 */
dtkComposerNodeNumberLong::~dtkComposerNodeNumberLong(void)
{
    delete d;

    d = NULL;
}

//! Updates the graphical aspect of the node.
/*! 
 *  
 */
void dtkComposerNodeNumberLong::touch(void)
{
    if (!this->isInteractive())
        this->setEditorText(QString::number(d->receiver->data()));

    dtkComposerNodeNumber::touch();
}

//! 
/*! 
 *  Reimplemented from dtkComposerNode.
 */
void dtkComposerNodeNumberLong::pull(dtkComposerEdge *route, dtkComposerNodeProperty *property)
{
    Q_UNUSED(route);
    Q_UNUSED(property);
}

//! 
/*! 
 *  Reimplemented from dtkComposerNode.
 */
void dtkComposerNodeNumberLong::run(void)
{
    if (this->isInteractive())
        d->emitter->setData(this->editorText().toLongLong());
    else
        d->emitter->setData(d->receiver->data());
}

//! 
/*! 
 *  Reimplemented from dtkComposerNode.
 */
void dtkComposerNodeNumberLong::push(dtkComposerEdge *route, dtkComposerNodeProperty *property)
{
    Q_UNUSED(route);
    Q_UNUSED(property);
}

//! 
/*! 
 *  Reimplemented from dtkComposerNode.
 */
dtkComposerNodeAbstractTransmitter *dtkComposerNodeNumberLong::emitter(dtkComposerNodeProperty *property)
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
bool dtkComposerNodeNumberLong::onLeftRouteConnected(dtkComposerEdge *route, dtkComposerNodeProperty *destination)
{
    Q_UNUSED(destination);

    if (!(d->receiver = dynamic_cast<dtkComposerNodeTransmitter<qlonglong> *> (route->source()->node()->emitter(route->source()))))
        return false;

    this->interactiveOff();

    return true;
}

//! 
/*! 
 *  Reimplemented from dtkComposerNode.
 */
bool dtkComposerNodeNumberLong::onRightRouteConnected(dtkComposerEdge *route, dtkComposerNodeProperty *property)
{
    return true;
}
