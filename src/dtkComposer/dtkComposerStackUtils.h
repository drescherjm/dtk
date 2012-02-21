/* dtkComposerStackUtils.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 20 16:07:10 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Feb 21 15:06:10 2012 (+0100)
 *           By: tkloczko
 *     Update #: 22
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERSTACKUTILS_H
#define DTKCOMPOSERSTACKUTILS_H

#include "dtkComposerTransmitter.h"

class dtkComposerSceneEdge;
class dtkComposerSceneNodeComposite;

void dtkComposerPropagateEdgeValidity(dtkComposerSceneNodeComposite *node, const dtkComposerTransmitterLinkList& valid_links, const dtkComposerTransmitterLinkList& invalid_links);

void    dtkComposerTransmitterConnection(dtkComposerSceneNodeComposite *root, dtkComposerSceneNodeComposite *node, dtkComposerSceneEdge *edge, bool propagate_edge_validity = true);
void dtkComposerTransmitterDisconnection(dtkComposerSceneNodeComposite *root, dtkComposerSceneNodeComposite *node, dtkComposerSceneEdge *edge, bool propagate_edge_validity = true);

#endif
