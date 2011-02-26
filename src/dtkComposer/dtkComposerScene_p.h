/* dtkComposerScene_p.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sat Feb 26 18:33:27 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Sat Feb 26 18:57:45 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 22
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERSCENE_P_H
#define DTKCOMPOSERSCENE_P_H

class dtkComposerEdge;
class dtkComposerNode;
class dtkComposerNodeFactory;

// /////////////////////////////////////////////////////////////////
// dtkComposerSceneClipboard
// /////////////////////////////////////////////////////////////////

class dtkComposerSceneClipboard
{
public:
    QList<dtkComposerNode *> nodes;
    QList<dtkComposerEdge *> edges;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerScenePrivate
// /////////////////////////////////////////////////////////////////

class dtkComposerScenePrivate
{
public:
    dtkComposerEdge *edge(dtkComposerEdge *edge);

public:
    dtkComposerNode *current_node; // current_node is NULL for the root, !NULL when inside a composite node.
    dtkComposerEdge *current_edge;

public:
    dtkComposerNodeFactory *factory;

public:
    bool modified;

public:
    QList<dtkComposerNode *> nodes;
    QList<dtkComposerEdge *> edges;

public:
    dtkComposerSceneClipboard clipboard;
};

#endif
