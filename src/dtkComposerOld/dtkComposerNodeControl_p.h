/* dtkComposerNodeControl_p.h --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Nov  7 16:06:43 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Dec 13 13:05:47 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 22
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
    QList<dtkComposerRoute *>  left_relay_routes;
    QList<dtkComposerRoute *> right_relay_routes;

    QList<dtkComposerRoute *>  left_active_routes;
    QList<dtkComposerRoute *> right_active_routes;

public:
    bool block_added;
    bool block_removed;

    bool running;

public:
    QColor color;
};

#endif
