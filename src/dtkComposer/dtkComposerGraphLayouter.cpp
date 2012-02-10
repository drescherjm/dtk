/* dtkComposerGraphLayouter.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Feb 10 10:17:18 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Feb 10 12:22:05 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 75
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerGraph.h"
#include "dtkComposerGraphEdge.h"
#include "dtkComposerGraphLayouter.h"
#include "dtkComposerGraphNode.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerGraphLayouterPrivate
// /////////////////////////////////////////////////////////////////

class dtkComposerGraphLayouterPrivate
{
public:
    dtkComposerGraph *graph;

public:
    void layout(void);

public:
    void removeCycles(void);
    void assignLayers(void);
    void assignPostns(void);
};

void dtkComposerGraphLayouterPrivate::layout(void)
{
    this->removeCycles();
    this->assignLayers();
    this->assignPostns();
}

void dtkComposerGraphLayouterPrivate::removeCycles(void)
{
    if(!this->graph)
        return;
}

void dtkComposerGraphLayouterPrivate::assignLayers(void)
{
    if(!this->graph)
        return;
}

void dtkComposerGraphLayouterPrivate::assignPostns(void)
{
    if(!this->graph)
        return;
    
    for(int i = 1; i < graph->nodes().count(); i++)
        graph->nodes().at(i)->setPos(graph->nodes().at(i-1)->pos() + QPointF(200, 0));
}

// /////////////////////////////////////////////////////////////////
// dtkComposerGraphLayouter
// /////////////////////////////////////////////////////////////////

dtkComposerGraphLayouter::dtkComposerGraphLayouter(void) : d(new dtkComposerGraphLayouterPrivate)
{
    d->graph = NULL;
}

dtkComposerGraphLayouter::~dtkComposerGraphLayouter(void)
{
    delete d;

    d = NULL;
}

void dtkComposerGraphLayouter::setGraph(dtkComposerGraph *graph)
{
    d->graph = graph;
}

void dtkComposerGraphLayouter::layout(void)
{
    d->layout();
}
