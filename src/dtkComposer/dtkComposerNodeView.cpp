/* dtkComposerNodeView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Jul 15 11:25:19 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Nov 26 15:03:59 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 54
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
