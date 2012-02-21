/* dtkComposerStackUtils.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 20 16:08:18 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Feb 21 15:09:27 2012 (+0100)
 *           By: tkloczko
 *     Update #: 76
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
#include "dtkComposerTransmitter.h"

void dtkComposerPropagateEdgeValidity(dtkComposerSceneNodeComposite *node, const dtkComposerTransmitterLinkList& valid_links, const dtkComposerTransmitterLinkList& invalid_links)
{
    dtkComposerTransmitter *s = NULL;
    dtkComposerTransmitter *d = NULL;

    foreach(dtkComposerSceneEdge *edge, node->edges()) {

        if (node != edge->source()->node())
            s = edge->source()->node()->wrapee()->emitters().at(edge->source()->id());
        else
            s = edge->source()->node()->wrapee()->receivers().at(edge->source()->id());

        if (node != edge->destination()->node())
            d = edge->destination()->node()->wrapee()->receivers().at(edge->destination()->id());
        else
            d = edge->destination()->node()->wrapee()->emitters().at(edge->destination()->id());

        foreach(dtkComposerTransmitterLink *link, invalid_links)
            if(link->source() == s && link->destination() == d)
                edge->invalidate();
        
        foreach(dtkComposerTransmitterLink *link, valid_links)
            if(link->source() == s && link->destination() == d)
                edge->validate();
    }

    foreach(dtkComposerSceneNode *node, node->nodes()) {

        if(dtkComposerSceneNodeComposite *composite = dynamic_cast<dtkComposerSceneNodeComposite *>(node)) {
            dtkComposerPropagateEdgeValidity(composite, valid_links, invalid_links);
        }

        if(dtkComposerSceneNodeControl *control = dynamic_cast<dtkComposerSceneNodeControl *>(node)) {
            foreach(dtkComposerSceneNodeComposite *block, control->blocks())
                dtkComposerPropagateEdgeValidity(block, valid_links, invalid_links);
        }
    }
}

void dtkComposerTransmitterConnection(dtkComposerSceneNodeComposite *root, dtkComposerSceneNodeComposite *node, dtkComposerSceneEdge *edge, bool propagate_edge_validity)
{
    dtkComposerTransmitter *s_t = NULL;

    if (node != edge->source()->node())
        s_t = edge->source()->node()->wrapee()->emitters().at(edge->source()->id());
    else
        s_t = edge->source()->node()->wrapee()->receivers().at(edge->source()->id());

    dtkComposerTransmitter *d_t = NULL;

    if (node != edge->destination()->node())
        d_t = edge->destination()->node()->wrapee()->receivers().at(edge->destination()->id());
    else
        d_t = edge->destination()->node()->wrapee()->emitters().at(edge->destination()->id());
    
    dtkComposerTransmitterLinkList   valid_edges;
    dtkComposerTransmitterLinkList invalid_edges;
    dtkComposerTransmitter::onTransmittersConnected(s_t, d_t, valid_edges, invalid_edges);

    if (propagate_edge_validity)
        dtkComposerPropagateEdgeValidity(root, valid_edges, invalid_edges);
}

void dtkComposerTransmitterDisconnection(dtkComposerSceneNodeComposite *root, dtkComposerSceneNodeComposite *node, dtkComposerSceneEdge *edge, bool propagate_edge_validity)
{
    dtkComposerTransmitter *s_t = NULL;

    if (node != edge->source()->node())
        s_t = edge->source()->node()->wrapee()->emitters().at(edge->source()->id());
    else
        s_t = edge->source()->node()->wrapee()->receivers().at(edge->source()->id());

    dtkComposerTransmitter *d_t = NULL;

    if (node != edge->destination()->node())
        d_t = edge->destination()->node()->wrapee()->receivers().at(edge->destination()->id());
    else
        d_t = edge->destination()->node()->wrapee()->emitters().at(edge->destination()->id());

    dtkComposerTransmitterLinkList invalid_edges;
    dtkComposerTransmitter::onTransmittersDisconnected(s_t, d_t, invalid_edges);

    if (propagate_edge_validity) {
        dtkComposerTransmitterLinkList   valid_edges;
        dtkComposerPropagateEdgeValidity(root, valid_edges, invalid_edges);
    }
}
