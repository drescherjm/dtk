/* dtkComposerGraph.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Feb  9 14:42:13 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Feb 10 12:22:44 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 44
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERGRAPH_H
#define DTKCOMPOSERGRAPH_H

#include <QtGui>

class dtkComposerGraphEdge;
class dtkComposerGraphEdgeList;
class dtkComposerGraphNode;
class dtkComposerGraphNodeList;
class dtkComposerGraphPrivate;
class dtkComposerSceneEdge;
class dtkComposerSceneNode;

class dtkComposerGraph : public QGraphicsScene
{
    Q_OBJECT

public:
     dtkComposerGraph(void);
    ~dtkComposerGraph(void);

public:
    void    addNode(dtkComposerSceneNode *node);
    void removeNode(dtkComposerSceneNode *node);

    void    addEdge(dtkComposerSceneEdge *edge);
    void removeEdge(dtkComposerSceneEdge *edge);

public:
    dtkComposerGraphEdgeList edges(void);
    dtkComposerGraphNodeList nodes(void);

public:
    void layout(void);

protected slots:
    void onSelectionChanged(void);

private:
    dtkComposerGraphPrivate *d;
};

#endif
