/* dtkComposerScene_p.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Jan 30 15:32:14 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Apr 11 09:11:06 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 276
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERSCENE_P_H
#define DTKCOMPOSERSCENE_P_H

#include "dtkComposerSceneEdge.h"
#include "dtkComposerSceneNode.h"

#include <QtWidgets>

class dtkComposerNodeFactory;
class dtkComposerGraph;
class dtkComposerSceneEdge;
class dtkComposerSceneNode;
class dtkComposerSceneNodeComposite;
class dtkComposerSceneNodeLeaf;
class dtkComposerSceneNote;
class dtkComposerStack;

class dtkComposerScenePrivate
{
public:
    dtkComposerNodeFactory *factory;
    dtkComposerStack *stack;
    dtkComposerGraph *graph;

public:
    dtkComposerSceneNodeComposite    *root_node;
    dtkComposerSceneNodeComposite *current_node;

public:
    dtkComposerSceneNodeList copy_nodes;

public:
    dtkComposerSceneEdgeList connected_edges;
    dtkComposerSceneEdgeList all_edges;
    dtkComposerSceneNodeList all_nodes;

public:
    bool masked_edges;

public:
    dtkComposerSceneEdge *current_edge;

public:
    QPointF reparent_origin_pos;
    QPointF reparent_target_pos;

    dtkComposerSceneNode *reparent_origin;
    dtkComposerSceneNode *reparent_target;
    dtkComposerSceneNode *last_paused_node;

public:
    QAction *flag_as_blue_action;
    QAction *flag_as_gray_action;
    QAction *flag_as_green_action;
    QAction *flag_as_orange_action;
    QAction *flag_as_pink_action;
    QAction *flag_as_red_action;
    QAction *flag_as_yellow_action;
    QAction *set_breakpoint_action;

public:
    QAction *mask_edges_action;
    QAction *unmask_edges_action;

public:
    QHash<Qt::GlobalColor, QList<dtkComposerSceneNodeLeaf *> > flagged_nodes;
};

#endif
