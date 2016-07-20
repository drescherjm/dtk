/* dtkComposerStackUtils.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 20 16:07:10 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Apr 11 10:17:01 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 39
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

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

