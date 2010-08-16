/* dtkComposerNodeProcess.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Jul 15 11:23:54 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Jul 26 12:39:26 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 81
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerEdge.h"
#include "dtkComposerNodeProcess.h"
#include "dtkComposerNodeProperty.h"

#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractProcess.h>
#include <dtkCore/dtkGlobal.h>

class dtkComposerNodeProcessPrivate
{
public:
    dtkComposerNodeProperty *property_input_file;
    dtkComposerNodeProperty *property_input_data;
    dtkComposerNodeProperty *property_output_data;
};

dtkComposerNodeProcess::dtkComposerNodeProcess(dtkComposerNode *parent) : dtkComposerNode(parent), d(new dtkComposerNodeProcessPrivate)
{
    d->property_input_data = new dtkComposerNodeProperty("data", dtkComposerNodeProperty::Input, dtkComposerNodeProperty::Single, this);
    d->property_input_file = new dtkComposerNodeProperty("file", dtkComposerNodeProperty::Input, dtkComposerNodeProperty::Single, this);
    d->property_output_data = new dtkComposerNodeProperty("data", dtkComposerNodeProperty::Output, dtkComposerNodeProperty::Single, this);

    this->setType(dtkComposerNode::Process);
    this->addInputProperty(d->property_input_data);
    this->addInputProperty(d->property_input_file);
    this->addOutputProperty(d->property_output_data);
}

dtkComposerNodeProcess::~dtkComposerNodeProcess(void)
{
    delete d;

    d = NULL;
}

QVariant dtkComposerNodeProcess::value(dtkComposerNodeProperty *property)
{
    if(property == d->property_output_data)
        if(dtkAbstractProcess *process = dynamic_cast<dtkAbstractProcess *>(this->object()))
            return qVariantFromValue(*(process->output()));

    return QVariant();
}

void dtkComposerNodeProcess::onInputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    if(property == d->property_input_file) {
        
        QString file = edge->source()->node()->value(edge->source()).toString();

        if(dtkAbstractProcess *process = dynamic_cast<dtkAbstractProcess *>(this->object()))
            process->read(file);
    }   

    if(property == d->property_input_data) {
        
        dtkAbstractData *data;

        if(dtkAbstractData *d = dynamic_cast<dtkAbstractData *>(edge->source()->node()->object()))
            data = d;

        if(dtkAbstractProcess *process = dynamic_cast<dtkAbstractProcess *>(edge->source()->node()->object()))
            data = process->output();

        if(dtkAbstractProcess *process = dynamic_cast<dtkAbstractProcess *>(this->object()))
            process->setInput(data);
    }
}

void dtkComposerNodeProcess::onOutputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    Q_UNUSED(edge);

    if(property == d->property_output_data) {
        if(dtkAbstractProcess *process = dynamic_cast<dtkAbstractProcess *>(this->object())) {
            connect(process, SIGNAL(progressed(int)), this, SIGNAL(progressed(int)));
            process->update();
            // disconnect(process, SIGNAL(progressed(int)), this, SIGNAL(progressed(int)));
        }
    }
}
