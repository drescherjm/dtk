/* dtkComposerNodeLog.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 28 20:51:32 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Nov  4 09:41:12 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 36
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

#include <dtkCore/dtkGlobal.h>
#include <dtkCore/dtkLog.h>

class dtkComposerNodeLogPrivate
{
public:
    dtkComposerNodeProperty *property_input_value;
};

dtkComposerNodeLog::dtkComposerNodeLog(dtkComposerNode *parent) : dtkComposerNode(parent), d(new dtkComposerNodeLogPrivate)
{
    d->property_input_value = new dtkComposerNodeProperty("value", dtkComposerNodeProperty::Input, dtkComposerNodeProperty::Multiple, this);

    this->setTitle("Log");
    this->setKind(dtkComposerNode::View);
    this->setType("dtkComposerLog");

    this->g->appendLeftProperty(d->property_input_value);
}

dtkComposerNodeLog::~dtkComposerNodeLog(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeLog::pull(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    Q_UNUSED(property);

    QVariant value = edge->source()->node()->value(edge->source());

    if(value.canConvert(QVariant::String))
        dtkOutput() << value.toString();
}

void dtkComposerNodeLog::run(void)
{
    return;
}
