/* dtkComposerNodeControl_p.h --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Nov  7 16:06:43 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Dec  7 15:26:01 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 20
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODECONTROL_P_H
#define DTKCOMPOSERNODECONTROL_P_H

#include <QtCore>

class dtkComposerEdge;
class dtkComposerNode;
class dtkComposerNodeControlBlock;
class dtkComposerNodeProperty;
class dtkComposerRoute;

class dtkComposerNodeControlPrivate
{
public:
    dtkComposerNodeControlBlock *current_block;

public:
    QList<dtkComposerNodeControlBlock *> blocks;

public:
    QMultiHash<dtkComposerNodeControlBlock *, dtkComposerNodeProperty *>  block_left_properties;
    QMultiHash<dtkComposerNodeControlBlock *, dtkComposerNodeProperty *> block_right_properties;

    QMultiHash<dtkComposerNodeControlBlock *, dtkComposerNode *> block_nodes;

public:
    dtkComposerNodeProperty *property_input;

public:
    QList<dtkComposerRoute *>  input_relay_routes;
    QList<dtkComposerRoute *> output_relay_routes;

    QList<dtkComposerRoute *>  input_active_routes;
    QList<dtkComposerRoute *> output_active_routes;

public:
    bool block_added;
    bool block_removed;

    bool running;

public:
    QColor color;
};

#endif
