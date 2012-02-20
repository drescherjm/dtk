/* dtkComposerStackUtils.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 20 16:07:10 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 20 16:39:28 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 14
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

class dtkComposerSceneNodeComposite;

void dtkComposerPropagateEdgeValidity(dtkComposerSceneNodeComposite *node, const dtkComposerTransmitterLinkList& valid_links, const dtkComposerTransmitterLinkList& invalid_links);

#endif
