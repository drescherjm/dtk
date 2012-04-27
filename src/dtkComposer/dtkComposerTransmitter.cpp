/* dtkComposerTransmitter.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Mon Jan 30 16:37:29 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Apr 26 15:18:36 2012 (+0200)
 *           By: tkloczko
 *     Update #: 191
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerTransmitter.h"
#include "dtkComposerTransmitter_p.h"
#include "dtkComposerTransmitterVariant.h"
#include "dtkComposerNode.h"

#include <dtkCore/dtkGlobal>

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitter implementation
// /////////////////////////////////////////////////////////////////

//! Constructs dtkComposerTransmitter with \a parent as parent node.
/*! 
 *  The parent node is the node that owns the transmitter in its list
 *  of emitters or receivers.
 */
dtkComposerTransmitter::dtkComposerTransmitter(dtkComposerNode *parent) : d(new dtkComposerTransmitterPrivate)
{
    d->active = true;
    d->required = true;
    d->parent = parent;
}

//! Destroys dtkComposerTransmitter.
/*!  
 *  
 */
dtkComposerTransmitter::~dtkComposerTransmitter(void)
{
    delete d;

    d = NULL;
}

QVariant dtkComposerTransmitter::variant(void) const
{
    return d->variant;
}

QVariant::Type dtkComposerTransmitter::type(void) const
{
    return d->variant.type();
}

QString dtkComposerTransmitter::typeName(void) const
{
    return QVariant::typeToName(d->variant.type());
}

//! 
/*!  
 *  
 */
void dtkComposerTransmitter::setParentNode(dtkComposerNode *parent)
{
    d->parent = parent;
}

//! Returns pointer to parent node.
/*!  
 *  
 */
dtkComposerNode *dtkComposerTransmitter::parentNode(void) const
{
    return d->parent;
}

//! Sets active flag to \a active.
/*! 
 *  Active flags is typically used to select an emitter among a list
 *  owned by a control node.
 */
void dtkComposerTransmitter::setActive(bool active)
{
    d->active = active;

    foreach(dtkComposerTransmitter *receiver, d->receivers)
        receiver->setActiveEmitter(this);
}

//! Returns true if transmitter is active.
/*! 
 *  Active flags is typically used to select an emitter among a list
 *  owned by a control node.
 */
bool dtkComposerTransmitter::active(void)
{
    return d->active;
}

//! Returns true if transmitter is active.
/*! 
 *  Active flags is typically used to select an emitter among a list
 *  owned by a control node.
 */
void dtkComposerTransmitter::setActiveEmitter(dtkComposerTransmitter *emitter)
{
    DTK_UNUSED(emitter);
}

//! Sets required flag to \a required.
/*! 
 *  Required flags is typically used to know whether a transmitter
 *  must be connected or not.
 */
void dtkComposerTransmitter::setRequired(bool required)
{
    d->required = required;
}

//! Returns true if transmitter is required.
/*! 
 *  Required flags is typically used to know whether a transmitter
 *  must be connected or not.
 */
bool dtkComposerTransmitter::required(void)
{
    return d->required;
}

//! Appends \a transmitter to the list of the transmitters that follow
//! the current one. 
/*! 
 *  This list contains only one reference to each transmitter.
 */
void dtkComposerTransmitter::appendNext(dtkComposerTransmitter *transmitter)
{
    if (d->next_list.contains(transmitter))
        return;

    d->next_list << transmitter;
}

//! Removes \a transmitter from the list of the transmitters that
//! follow the current one.
/*! 
 *  
 */
void dtkComposerTransmitter::removeNext(dtkComposerTransmitter *transmitter)
{
    d->next_list.removeOne(transmitter);
}

//! Appends \a transmitter to the list of the transmitters that precede
//! the current one.
/*! 
 *  This list contains only one reference to each transmitter.
 */
void dtkComposerTransmitter::appendPrevious(dtkComposerTransmitter *transmitter)
{
    if (d->previous_list.contains(transmitter))
        return;

    d->previous_list << transmitter;
}

//! Removes \a transmitter from the list of the transmitters that
//! precede the current one.
/*! 
 *  
 */
void dtkComposerTransmitter::removePrevious(dtkComposerTransmitter *transmitter)
{
    d->previous_list.removeOne(transmitter);
}

// //! Returns a shared copy of the list of the transmitters that follow
// //! the current one.
// /*! 
//  *  
//  */
// QList<dtkComposerTransmitter *> dtkComposerTransmitter::nextList(void)
// {
//     return d->next_list;
// }

// //! Returns a shared copy of the list of the transmitters that precede
// //! the current one.
// /*! 
//  *  
//  */
// QList<dtkComposerTransmitter *> dtkComposerTransmitter::previousList(void)
// {
//     return d->previous_list;
// }

//! Returns true when current transmitter and \a transmitter share
//! data of same type.
/*! 
 *  In practice, this method is only reimplemented in
 *  dtkComposerReceiver class where the type checking is performed.
 *
 *  By default, false is returned.
 */
bool dtkComposerTransmitter::connect(dtkComposerTransmitter *transmitter)
{
    DTK_UNUSED(transmitter);

    return false;
}

//! 
/*! 
 *  
 */
void dtkComposerTransmitter::appendReceiver(dtkComposerTransmitter *receiver)
{
    d->receivers << receiver;
}

//! 
/*! 
 *  
 */
void dtkComposerTransmitter::removeReceiver(dtkComposerTransmitter *receiver)
{
    d->receivers.removeAll(receiver);
}

//! Returns true when current transmitter and \a transmitter share
//! data of same type.
/*! 
 *  In practice, this method is only reimplemented in
 *  dtkComposerReceiver class where the type checking is performed.
 *
 *  By default, false is returned.
 */
bool dtkComposerTransmitter::disconnect(dtkComposerTransmitter *transmitter)
{
    DTK_UNUSED(transmitter);

    return false;
}

//! Finds all emitters connected to \a transmitter.
/*! 
 *  All links from every emitter found to \a transmitter are stored in
 *  a multi-hash table.
 *
 *  By default, an empty multi-hash is returned.
 */
dtkComposerTransmitter::LinkMap dtkComposerTransmitter::leftLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list)
{
    DTK_UNUSED(transmitter);
    DTK_UNUSED(list);

    return LinkMap();
}

//! Finds all receivers connected to \a transmitter.
/*! 
 *  All links from every receiver found to \a transmitter are stored
 *  in a multi-hash table.
 *
 *  By default, an empty multi-hash is returned.
 */
dtkComposerTransmitter::LinkMap dtkComposerTransmitter::rightLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list)
{
    DTK_UNUSED(transmitter);
    DTK_UNUSED(list);

    return LinkMap();
}

//! Connects all emitters and all receivers that share the link (\a
//! source, \a destination).
/*! 
 *  All links from \a destination to all likely emitters are first
 *  computed. Second, all paths from \a source to all possible receivers
 *  are also computed. Then, every receiver trys to connect each
 *  emitter. For every valid connection, the corresponding links
 *  between receiver and emitter are stored in \a
 *  valid_list. Otherwise, they are stored in \a invalid_list.
 */
bool dtkComposerTransmitter::onTransmittersConnected(dtkComposerTransmitter *source, dtkComposerTransmitter *destination, dtkComposerTransmitterLinkList& valid_links, dtkComposerTransmitterLinkList& invalid_links)
{
    source->appendNext(destination);
    destination->appendPrevious(source);

    dtkComposerTransmitterLinkList list;
    list << new dtkComposerTransmitterLink(source, destination);

    LinkMap  left_link_map =  source->leftLinks(destination, list);
    LinkMap right_link_map = destination->rightLinks(source, list);

    foreach(dtkComposerTransmitter *receiver, right_link_map.uniqueKeys()) {

        foreach(dtkComposerTransmitter *emitter, left_link_map.uniqueKeys()) {

            if (receiver->connect(emitter)) {

                // Add feedback to parent node in order to update all
                // transmitters !!!  Very useful for number nodes for
                // instance that need to check compatibility of
                // input/output types.

                foreach(dtkComposerTransmitterLink *l, right_link_map.values(receiver))
                    if(!valid_links.contains(l))
                        valid_links << l;
                foreach(dtkComposerTransmitterLink *l, left_link_map.values(emitter))
                    if(!valid_links.contains(l))
                        valid_links << l;
            
            } else {

                foreach(dtkComposerTransmitterLink *l, right_link_map.values(receiver))
                    if(!invalid_links.contains(l))
                        invalid_links << l;
                foreach(dtkComposerTransmitterLink *l, left_link_map.values(emitter))
                    if(!invalid_links.contains(l))
                        invalid_links << l;

            }
        }
    }

    return true;
}

//! Connects all emitters and all receivers that share the link (\a
//! source, \a destination).
/*! 
 *  All links from \a destination to all likely emitters are first
 *  computed. Second, all paths from \a source to all possible receivers
 *  are also computed. Then, every receiver trys to connect each
 *  emitter. For every valid connection, the corresponding links
 *  between receiver and emitter are stored in \a
 *  valid_list. Otherwise, they are stored in \a invalid_list.
 */
bool dtkComposerTransmitter::onTransmittersDisconnected(dtkComposerTransmitter *source, dtkComposerTransmitter *destination, dtkComposerTransmitterLinkList& invalid_links)
{
    source->removeNext(destination);
    destination->removePrevious(source);

    dtkComposerTransmitterLinkList list;
    list << new dtkComposerTransmitterLink(source, destination);

    LinkMap  left_link_map =  source->leftLinks(destination, list);
    LinkMap right_link_map = destination->rightLinks(source, list);

    foreach(dtkComposerTransmitter *receiver, right_link_map.uniqueKeys()) {

        foreach(dtkComposerTransmitter *emitter, left_link_map.uniqueKeys()) {

            receiver->disconnect(emitter);

            foreach(dtkComposerTransmitterLink *l, right_link_map.values(receiver))
                if(!invalid_links.contains(l))
                    invalid_links << l;
            foreach(dtkComposerTransmitterLink *l, left_link_map.values(emitter))
                if(!invalid_links.contains(l))
                    invalid_links << l;

        }
    }

    return true;
}

// /////////////////////////////////////////////////////////////////
// Debug operators
// /////////////////////////////////////////////////////////////////

//! Writes the transmitter's identifier to the stream.
/*! 
 *  
 */
QDebug operator<<(QDebug debug, const dtkComposerTransmitter& transmitter)
{
    debug.nospace() << "dtkComposerTransmitter:" << transmitter.kindName() << transmitter.typeName();
    
    return debug.space();
}

//!  Writes the transmitter's identifier to the stream.
/*! 
 *  
 */
QDebug operator<<(QDebug debug, dtkComposerTransmitter *transmitter)
{
    debug.nospace() << "dtkComposerTransmitter:" << transmitter->kindName() << transmitter->typeName();
    
    return debug.space();
}

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterLinkPrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerTransmitterLinkPrivate
{
public:
    dtkComposerTransmitter *source;
    dtkComposerTransmitter *destination;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterLink implementation
// /////////////////////////////////////////////////////////////////

dtkComposerTransmitterLink::dtkComposerTransmitterLink(dtkComposerTransmitter *source, dtkComposerTransmitter *destination) : d(new dtkComposerTransmitterLinkPrivate)
{
    d->source = source;
    d->destination = destination;
}

dtkComposerTransmitterLink::~dtkComposerTransmitterLink(void)
{
    delete d;
    
    d = NULL;
}

dtkComposerTransmitter *dtkComposerTransmitterLink::source(void)
{
    return d->source;
}

dtkComposerTransmitter *dtkComposerTransmitterLink::destination(void)
{
    return d->destination;
}
