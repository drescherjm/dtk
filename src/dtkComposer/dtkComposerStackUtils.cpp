/* dtkComposerStackUtils.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 20 16:08:18 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Feb 20 17:02:29 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 35
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNode.h"
#include "dtkComposerSceneEdge.h"
#include "dtkComposerSceneNode.h"
#include "dtkComposerSceneNodeComposite.h"
#include "dtkComposerSceneNodeControl.h"
#include "dtkComposerScenePort.h"
#include "dtkComposerStackUtils.h"

void dtkComposerPropagateEdgeValidity(dtkComposerSceneNodeComposite *node, const dtkComposerTransmitterLinkList& valid_links, const dtkComposerTransmitterLinkList& invalid_links)
{
    foreach(dtkComposerSceneEdge *edge, node->edges()) {
        dtkComposerTransmitter *s = edge->source()->node()->wrapee()->emitters().at(edge->source()->id());
        dtkComposerTransmitter *d = edge->destination()->node()->wrapee()->receivers().at(edge->destination()->id());

        foreach(dtkComposerTransmitterLink *link, invalid_links)
            if(link->source() == s && link->destination() == d)
                edge->invalidate();
        
        foreach(dtkComposerTransmitterLink *link, valid_links)
            if(link->source() == s && link->destination() == d)
                edge->validate();
    }

    foreach(dtkComposerSceneNode *node, node->nodes()) {

        if(dtkComposerSceneNodeComposite *composite = dynamic_cast<dtkComposerSceneNodeComposite *>(node))
            dtkComposerPropagateEdgeValidity(composite, valid_links, invalid_links);

        if(dtkComposerSceneNodeControl *control = dynamic_cast<dtkComposerSceneNodeControl *>(node)) {

            foreach(dtkComposerSceneNodeComposite *block, control->blocks())
                dtkComposerPropagateEdgeValidity(block, valid_links, invalid_links);
        }
    }
}
