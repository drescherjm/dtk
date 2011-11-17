/* dtkComposerNodeLog.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 28 20:51:32 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Nov 17 15:32:58 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 143
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerEdge.h"
#include "dtkComposerNodeLog.h"
#include "dtkComposerNodeProperty.h"
#include "dtkComposerNodeTransmitter.h"

#include <dtkCore/dtkGlobal.h>
#include <dtkCore/dtkLog.h>

#include <QtCore>

#include <typeinfo>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLogPrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeLogPrivate
{
public:
    dtkComposerNodeProperty *property_left_value;

    dtkComposerNodeAbstractTransmitter *receiver;

public:
    QString type_bool;
    QString type_int;
    QString type_uint;
    QString type_long;
    QString type_ulong;
    QString type_llong;
    QString type_ullong;
    QString type_float;
    QString type_double;
    QString type_string;
    QString type_string_list;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeLog implementation
// /////////////////////////////////////////////////////////////////

//! Constructs logger node.
/*! 
 *  
 */
dtkComposerNodeLog::dtkComposerNodeLog(dtkComposerNode *parent) : dtkComposerNode(parent), d(new dtkComposerNodeLogPrivate)
{
    d->property_left_value = new dtkComposerNodeProperty("value", dtkComposerNodeProperty::Left, dtkComposerNodeProperty::AsInput, dtkComposerNodeProperty::Multiple, this);

    this->setTitle("Log");
    this->setKind(dtkComposerNode::View);
    this->setType("dtkComposerLog");

    this->g->appendLeftProperty(d->property_left_value);

    d->type_bool        = typeid(bool).name();
    d->type_int         = typeid(int).name();
    d->type_uint        = typeid(uint).name();
    d->type_long        = typeid(long).name();
    d->type_ulong       = typeid(ulong).name();
    d->type_llong       = typeid(qlonglong).name();
    d->type_ullong      = typeid(qulonglong).name();
    d->type_float       = typeid(float).name();
    d->type_double      = typeid(double).name();
    d->type_string      = typeid(QString).name();
    d->type_string_list = typeid(QStringList).name();

    d->receiver = NULL;
}

//! Destroys logger node.
/*! 
 *  
 */
dtkComposerNodeLog::~dtkComposerNodeLog(void)
{
    delete d;

    d = NULL;
}

//! Casts the receiver into the correct type before logging the data
//! it contains.
/*! 
 *  Reimplemented from dtkComposerNode.
 */
void dtkComposerNodeLog::pull(dtkComposerEdge *route, dtkComposerNodeProperty *property)
{
    Q_UNUSED(property);

    d->receiver = route->source()->node()->emitter(route->source());

    QString type = d->receiver->metadata("Type");

    if (type == d->type_bool)
       dtkOutput() << static_cast<dtkComposerNodeTransmitter<bool> *>(d->receiver)->data();

    else if (type == d->type_int)
        dtkOutput() << static_cast<dtkComposerNodeTransmitter<int> *>(d->receiver)->data();

    else if (type == d->type_uint)
        dtkOutput() << static_cast<dtkComposerNodeTransmitter<uint> *>(d->receiver)->data();

    else if (type == d->type_long)
       dtkOutput() << static_cast<dtkComposerNodeTransmitter<long> *>(d->receiver)->data();

    else if (type == d->type_ulong)
        dtkOutput() << static_cast<dtkComposerNodeTransmitter<ulong> *>(d->receiver)->data();

    else if (type == d->type_llong)
        dtkOutput() << static_cast<dtkComposerNodeTransmitter<qlonglong> *>(d->receiver)->data();

    else if (type == d->type_ullong)
        dtkOutput() << static_cast<dtkComposerNodeTransmitter<qulonglong> *>(d->receiver)->data();

    else if (type == d->type_float)
        dtkOutput() << static_cast<dtkComposerNodeTransmitter<float> *>(d->receiver)->data();  

    else if (type == d->type_double)
        dtkOutput() << static_cast<dtkComposerNodeTransmitter<double> *>(d->receiver)->data();

    else if (type == d->type_string)
        dtkOutput() << static_cast<dtkComposerNodeTransmitter<QString> *>(d->receiver)->data();

    else if (type == d->type_string_list)
        dtkOutput() << static_cast<dtkComposerNodeTransmitter<QStringList> *>(d->receiver)->data();

    else
        dtkOutput() << type << " is not supported by the logger.";
}

//! 
/*! 
 *  Reimplemented from dtkComposerNode.
 */
void dtkComposerNodeLog::run(void)
{
    return;
}

//! 
/*! 
 *  Reimplemented from dtkComposerNode.
 */
bool dtkComposerNodeLog::setReceiver(dtkComposerEdge *route, dtkComposerNodeProperty *destination)
{        
    return true;
}
