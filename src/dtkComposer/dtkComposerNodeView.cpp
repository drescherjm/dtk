/* dtkComposerNodeView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Jul 15 11:25:19 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Apr  8 16:37:14 2011 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 61
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

void dtkComposerNodeView::pull(dtkComposerEdge *edge, dtkComposerNodeProperty *property)
{
    DTK_UNUSED(edge);
    DTK_UNUSED(property);
}

void dtkComposerNodeView::run(void)
{
    return;
}
