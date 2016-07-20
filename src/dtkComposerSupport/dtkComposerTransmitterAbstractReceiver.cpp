/* dtkComposerTransmitterAbstractReceiver.cpp ---
 *
 * Author: Thibaud Kloczko, Inria.
 * Created: 2012 Thu Oct 11 12:29:44 (+0200)
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkComposerTransmitterAbstractReceiver.h"

#include <dtkCoreSupport/dtkGlobal>

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterAbstractReceiver implementation
// /////////////////////////////////////////////////////////////////

dtkComposerTransmitterAbstractReceiver::dtkComposerTransmitterAbstractReceiver(dtkComposerNode *parent) : dtkComposerTransmitter(parent)
{

}

dtkComposerTransmitterAbstractReceiver::~dtkComposerTransmitterAbstractReceiver(void)
{

}

//!
/*!
 *  All links from every receiver found to \a transmitter are stored
 *  in a multi-hash table.
 *
 *  By default, an empty multi-hash is returned.
 */
dtkComposerTransmitter::LinkMap dtkComposerTransmitterAbstractReceiver::rightLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list)
{
    DTK_UNUSED(transmitter);

    LinkMap link_map;

    foreach (dtkComposerTransmitterLink *l, list)
        link_map.insert(this, l);

    return link_map;
}
