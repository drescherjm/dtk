/* dtkComposerNodeView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Jul 15 11:25:19 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Jul 26 14:43:54 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 42
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerEdge.h"
#include "dtkComposerNodeView.h"
#include "dtkComposerNodeProperty.h"

#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractProcess.h>
#include <dtkCore/dtkAbstractView.h>
#include <dtkCore/dtkGlobal.h>

class dtkComposerNodeViewPrivate
{
public:
    dtkComposerNodeProperty *property_input_data;
};

dtkComposerNodeView::dtkComposerNodeView(dtkComposerNode *parent) : dtkComposerNode(parent), d(new dtkComposerNodeViewPrivate)
{
    d->property_input_data = new dtkComposerNodeProperty("data", dtkComposerNodeProperty::Input, dtkComposerNodeProperty::Multiple, this);

    this->setType(dtkComposerNode::View);
    this->addInputProperty(d->property_input_data);
}

dtkComposerNodeView::~dtkComposerNodeView(void)
{
    delete d;

    d = NULL;
}

void dtkComposerNodeView::onInputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    if(property == d->property_input_data) {

        dtkAbstractView *view = dynamic_cast<dtkAbstractView *>(this->object());

        dtkAbstractData *data = NULL;

        if(dtkAbstractProcess *process = dynamic_cast<dtkAbstractProcess *>(edge->source()->node()->object()))
            data = process->output();

        if(data && view)
            view->setData(data);
    }
}
