/* dtkComposerGraph.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Feb  9 14:42:13 2012 (+0100)
 * Version: $Id$
 * Last-Updated: mar. févr. 28 10:27:33 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 56
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

    void createGroup(dtkComposerSceneNode *node);
    void destroyGroup(dtkComposerSceneNode *node);
    void removeGroup(dtkComposerSceneNode *node);

public:
    dtkComposerGraphEdgeList edges(void);
    dtkComposerGraphNodeList nodes(void);

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

protected slots:
    void onSelectionChanged(void);

private:
    dtkComposerGraphPrivate *d;
};

#endif
