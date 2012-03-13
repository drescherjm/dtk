/* dtkComposerScene_p.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Jan 30 15:32:14 2012 (+0100)
 * Version: $Id$
 * Last-Updated: mar. mars 13 09:27:10 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 218
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERSCENE_P_H
#define DTKCOMPOSERSCENE_P_H

#include <QtGui>

class dtkComposerEvaluator;
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
    dtkComposerEvaluator *evaluator;

public:
    dtkComposerSceneNodeComposite    *root_node;
    dtkComposerSceneNodeComposite *current_node;

public:
    dtkComposerSceneEdge *current_edge;

public:
    QPointF reparent_origin_pos;
    QPointF reparent_target_pos;

    dtkComposerSceneNode *reparent_origin;
    dtkComposerSceneNode *reparent_target;
};

#endif
