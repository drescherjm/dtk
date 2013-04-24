/* dtkComposerQuickGraph.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Fri Apr 19 10:59:28 2013 (+0200)
 * Version: 
 * Last-Updated: Fri Apr 19 11:01:29 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 5
 */

/* Change Log:
 * 
 */

#include "dtkComposerQuickGraph.h"

class dtkComposerQuickGraphPrivate
{
public:
    dtkComposerGraph *graph;
};

dtkComposerQuickGraph::dtkComposerQuickGraph(QObject *parent) : QObject(parent), d(new dtkComposerQuickGraphPrivate)
{
    d->graph = new dtkComposerGraph;
}

dtkComposerQuickGraph::~dtkComposerQuickGraph(void)
{
    delete d->graph;
    delete d;
}

dtkComposerGraph *dtkComposerQuickGraph::graph(void)
{
    return d->graph;
}
