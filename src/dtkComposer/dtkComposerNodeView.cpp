/* dtkComposerNodeView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Jul 15 11:25:19 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Feb 17 16:50:39 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 58
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
};

dtkComposerNodeView::dtkComposerNodeView(dtkComposerNode *parent) : dtkComposerNode(parent), d(new dtkComposerNodeViewPrivate)
{
    this->setKind(dtkComposerNode::View);
}

dtkComposerNodeView::~dtkComposerNodeView(void)
{
    if(this->object())
        delete this->object();

    delete d;

    d = NULL;
}

void dtkComposerNodeView::onInputEdgeConnected(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    Q_UNUSED(edge);
    Q_UNUSED(property);
}

void dtkComposerNodeView::run(void)
{
    return;
}
