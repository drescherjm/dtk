/* dtkComposerNodeLog.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 28 20:51:32 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Nov 16 10:46:28 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 103
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

class dtkComposerNodeLogPrivate
{
public:
    dtkComposerNodeProperty *property_input_value;

    QHash<dtkComposerEdge *, dtkComposerNodeAbstractTransmitter *> receivers;

    QHash<dtkComposerEdge *, QVariant::Type> types;

    QString message;

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

dtkComposerNodeLog::dtkComposerNodeLog(dtkComposerNode *parent) : dtkComposerNode(parent), d(new dtkComposerNodeLogPrivate)
{
    d->property_input_value = new dtkComposerNodeProperty("value", dtkComposerNodeProperty::Left, dtkComposerNodeProperty::AsInput, dtkComposerNodeProperty::Multiple, this);

    this->setTitle("Log");
    this->setKind(dtkComposerNode::View);
    this->setType("dtkComposerLog");

    this->g->appendLeftProperty(d->property_input_value);

    d->type_int         = typeid(int).name();
    d->type_uint        = typeid(uint).name();
    d->type_long        = typeid(long).name();
    d->type_ulong       = typeid(ulong).name();
    d->type_long        = typeid(qlonglong).name();
    d->type_ullong      = typeid(qulonglong).name();
    d->type_float       = typeid(float).name();
    d->type_double      = typeid(double).name();
    d->type_string      = typeid(QString).name();
    d->type_string_list = typeid(QStringList).name();
}

dtkComposerNodeLog::~dtkComposerNodeLog(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeLog::pull(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    Q_UNUSED(property);

    QString type = d->receivers.value(edge)->metadata("Type");

    if (type == d->type_int)
        d->message = QString("%1").arg(static_cast<dtkComposerNodeTransmitter<int> *>(d->receivers.value(edge))->data());

    else if (type == d->type_uint)
        d->message = QString("%1").arg(static_cast<dtkComposerNodeTransmitter<uint> *>(d->receivers.value(edge))->data());

    else if (type == d->type_long)
        d->message = QString("%1").arg(static_cast<dtkComposerNodeTransmitter<long> *>(d->receivers.value(edge))->data());

    else if (type == d->type_ulong)
        d->message = QString("%1").arg(static_cast<dtkComposerNodeTransmitter<ulong> *>(d->receivers.value(edge))->data());

    else if (type == d->type_llong)
        d->message = QString("%1").arg(static_cast<dtkComposerNodeTransmitter<qlonglong> *>(d->receivers.value(edge))->data());

    else if (type == d->type_ullong)
        d->message = QString("%1").arg(static_cast<dtkComposerNodeTransmitter<qulonglong> *>(d->receivers.value(edge))->data());

    else if (type == d->type_float)
          d->message = QString("%1").arg(static_cast<dtkComposerNodeTransmitter<float> *>(d->receivers.value(edge))->data());  

    else if (type == d->type_double)
            d->message = QString("%1").arg(static_cast<dtkComposerNodeTransmitter<double> *>(d->receivers.value(edge))->data());

    else if (type == d->type_string)
        d->message = QString("%1").arg(static_cast<dtkComposerNodeTransmitter<QString> *>(d->receivers.value(edge))->data());

    else if (type == d->type_string_list)
        d->message = QString("%1").arg(static_cast<dtkComposerNodeTransmitter<QStringList> *>(d->receivers.value(edge))->data().first());
    
    dtkOutput() << d->message;
}

void dtkComposerNodeLog::run(void)
{
    return;
}

bool dtkComposerNodeLog::onLeftRouteConnected(dtkComposerEdge *route)
{
    d->receivers.insert(route, route->source()->node()->emitter(route->source()));
        
    return dtkComposerNode::onLeftRouteConnected(route);
}
