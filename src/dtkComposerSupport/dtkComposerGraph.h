/* dtkComposerGraph.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Feb  9 14:42:13 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Jan 16 13:32:16 2014 (+0100)
 *           By: Selim Kraria
 *     Update #: 94
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERGRAPH_H
#define DTKCOMPOSERGRAPH_H

#include "dtkComposerSupportExport.h"

#include <QtWidgets>

class dtkComposerGraphEdge;
class dtkComposerGraphEdgeList;
class dtkComposerGraphNode;
class dtkComposerGraphNodeList;
class dtkComposerGraphPrivate;
class dtkComposerSceneEdge;
class dtkComposerSceneNode;
class dtkGraph;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerGraph : public QGraphicsScene
{
    Q_OBJECT

public:
    dtkComposerGraph(void);
    ~dtkComposerGraph(void);

public:
    void    addNode(dtkComposerSceneNode *node);
    void removeNode(dtkComposerSceneNode *node);

    void    addBlock(dtkComposerSceneNode *node);
    void removeBlock(dtkComposerSceneNode *node);

    void    addEdge(dtkComposerSceneEdge *edge);
    void removeEdge(dtkComposerSceneEdge *edge);

    void reparentNode(dtkComposerSceneNode *node, dtkComposerSceneNode *newparent);

    void createGroup(dtkComposerSceneNode *node);
    void destroyGroup(dtkComposerSceneNode *node);
    void removeGroup(dtkComposerSceneNode *node);

public:
    dtkComposerGraphNode *root(void);

public:
    dtkComposerGraphEdgeList edges(void);
    dtkComposerGraphNodeList nodes(void);
    dtkGraph graph(void);
    dtkGraph subgraph(dtkComposerGraphNode *from, dtkComposerGraphNode *to);

// --

public:
    void removeNode(dtkComposerGraphNode *node);
    void removeEdge(dtkComposerGraphEdge *edge);
// --

public:
    void clear(void);
    void layout(void);

public:
    QString toString(void);

signals:
    void cleared(void);

protected slots:
    void onSelectionChanged(void);

private:
    dtkComposerGraphPrivate *d;
};

#endif
