/* dtkComposerGraph.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Feb  9 14:42:13 2012 (+0100)
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#pragma once

#include "dtkComposerExport.h"

#include <QtWidgets>

class dtkComposerGraphEdge;
class dtkComposerGraphEdgeList;
class dtkComposerGraphNode;
class dtkComposerGraphNodeList;
class dtkComposerGraphPrivate;
class dtkComposerEdge;
class dtkComposerNode;
class dtkComposerNodeComposite;
class dtkGraph;

class DTKCOMPOSER_EXPORT dtkComposerGraph : public QObject
{
    Q_OBJECT

public:
     dtkComposerGraph(void);
    ~dtkComposerGraph(void);

public:
    void    addNode(dtkComposerNode *node, dtkComposerNode *parent);
    void removeNode(dtkComposerNode *node, dtkComposerNode *parent);

    void    addBlock(dtkComposerNode *node);
    void removeBlock(dtkComposerNode *node, dtkComposerNode *parent);

    void    addEdge(dtkComposerNode *source, dtkComposerNode *destination, QString src_type, QString dst_type);
    void removeEdge(dtkComposerNode *source, dtkComposerNode *destination, QString src_type, QString dst_type, dtkComposerNode *parent);
    /* void removeEdge(dtkComposerNode *source, dtkComposerNode *destination, dtkComposerNode *source_parent, dtkComposerNode *dest_parent, dtkComposerNode *source_owner_parent, dtkComposerNode *dest_owner_parent); */

    void reparentNode(dtkComposerNode *node, dtkComposerNode *oldparent, dtkComposerNode *newparent);

    void createGroup(dtkComposerNode *node, dtkComposerNode *parent);
    void destroyGroup(dtkComposerNode *node, dtkComposerNode *parent);
    void removeGroup(dtkComposerNode *node, dtkComposerNode *parent);

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

public:
    QString toString(void);

signals:
    void cleared(void);

private:
    dtkComposerGraphPrivate *d;
};
