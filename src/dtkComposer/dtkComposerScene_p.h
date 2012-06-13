/* dtkComposerScene_p.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Jan 30 15:32:14 2012 (+0100)
 * Version: $Id$
 * Last-Updated: ven. juin  8 16:31:47 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 242
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERSCENE_P_H
#define DTKCOMPOSERSCENE_P_H

#include "dtkComposerSceneNode.h"

#include <QtGui>

class dtkComposerFactory;
class dtkComposerGraph;
class dtkComposerMachine;
class dtkComposerSceneEdge;
class dtkComposerSceneNode;
class dtkComposerSceneNodeComposite;
class dtkComposerSceneNodeLeaf;
class dtkComposerSceneNote;
class dtkComposerStack;

class dtkComposerScenePrivate
{
public:
    dtkComposerMachine *machine;
    dtkComposerFactory *factory;
    dtkComposerStack *stack;
    dtkComposerGraph *graph;

public:
    dtkComposerSceneNodeComposite    *root_node;
    dtkComposerSceneNodeComposite *current_node;

public:
    dtkComposerSceneNodeList copy_nodes;

public:
    dtkComposerSceneEdge *current_edge;

public:
    QPointF reparent_origin_pos;
    QPointF reparent_target_pos;

    dtkComposerSceneNode *reparent_origin;
    dtkComposerSceneNode *reparent_target;
};

#endif
