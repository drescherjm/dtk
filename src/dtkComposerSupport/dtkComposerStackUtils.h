/* dtkComposerStackUtils.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 20 16:07:10 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Mar  1 13:13:42 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 38
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
class dtkComposerSceneNode;
class dtkComposerSceneNodeComposite;
class dtkComposerSceneNodeList;
class dtkComposerSceneNote;
class dtkComposerSceneNoteList;

// /////////////////////////////////////////////////////////////////
// Transmitter utils
// /////////////////////////////////////////////////////////////////

void dtkComposerPropagateEdgeValidity(dtkComposerSceneNodeComposite *node, const dtkComposerTransmitterLinkList& valid_links, const dtkComposerTransmitterLinkList& invalid_links);

void    dtkComposerTransmitterConnection(dtkComposerSceneNodeComposite *root, dtkComposerSceneNodeComposite *node, dtkComposerSceneEdge *edge, bool propagate_edge_validity = true);
void dtkComposerTransmitterDisconnection(dtkComposerSceneNodeComposite *root, dtkComposerSceneNodeComposite *node, dtkComposerSceneEdge *edge, bool propagate_edge_validity = true);

// /////////////////////////////////////////////////////////////////
// Genealogy utils
// /////////////////////////////////////////////////////////////////

bool areBrothers(dtkComposerSceneNodeList nodes);
bool areBrothers(dtkComposerSceneNoteList notes);
bool areBrothers(dtkComposerSceneNodeList nodes, dtkComposerSceneNoteList notes);

#endif
