/* dtkComposerGraphEdge.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Feb  9 15:09:22 2012 (+0100)
 * Version: $Id$
 * Last-Updated: jeu. sept.  5 17:06:03 2013 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 167
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerGraphEdge.h"
#include "dtkComposerGraphNode.h"


class dtkComposerGraphEdgePrivate
{
public:
    int id;
};

dtkComposerGraphEdge::dtkComposerGraphEdge(void) : dtkGraphEdge(), d(new dtkComposerGraphEdgePrivate)
{
    d->id = 0;
}

dtkComposerGraphEdge::~dtkComposerGraphEdge(void)
{
    delete d;

    d = NULL;
}

int dtkComposerGraphEdge::id(void)
{
    return d->id;
}

dtkComposerGraphNode *dtkComposerGraphEdge::source(void) const
{
    return reinterpret_cast<dtkComposerGraphNode *>(dtkGraphEdge::source());
}

dtkComposerGraphNode *dtkComposerGraphEdge::destination(void) const
{
    return reinterpret_cast<dtkComposerGraphNode *>(dtkGraphEdge::destination());
}

void dtkComposerGraphEdge::setId(int id)
{
    d->id = id;
}


// /////////////////////////////////////////////////////////////////
// dtkComposerGraphEdgeList
// /////////////////////////////////////////////////////////////////

dtkComposerGraphEdgeList::dtkComposerGraphEdgeList(void) : QList<dtkComposerGraphEdge *>()
{

}

dtkComposerGraphEdgeList::dtkComposerGraphEdgeList(const QList<dtkComposerGraphEdge *>& other) : QList<dtkComposerGraphEdge *>(other)
{

}
