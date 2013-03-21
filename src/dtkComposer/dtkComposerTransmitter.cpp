/* dtkComposerTransmitter.cpp --- 
 * 
 * Author: Thibaud Kloczko, Inria.
 * Created: Mon Jan 30 16:37:29 2012 (+0100)
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
#include "dtkComposerMetatype.h"
#include "dtkComposerNode.h"

#include <dtkContainer/dtkAbstractContainerWrapper.h>
#include <dtkCore/dtkAbstractObject>
#include <dtkCore/dtkGlobal>

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitter implementation
// /////////////////////////////////////////////////////////////////

//! Constructs dtkComposerTransmitter with \a parent as parent node.
/*! 
 *  The parent node is the node that owns the transmitter in its list
 *  of emitters or receivers.
 */
dtkComposerTransmitter::dtkComposerTransmitter(dtkComposerNode *parent) : d(new dtkComposerTransmitterPrivate(parent))
{

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

//! 
/*!  
 *  
 */
void dtkComposerTransmitter::clearData(void)
{

}


//! Several cases can occur when calling this method.
/*!  
 *  A transmitter can be either an emitter, a receiver or a
 *  variant. The case of the proxy is forgotten since this method must
 *  not be called in this case.
 *
 *  - Emitter case: the returned variant contains the data that has
 *    been passed to the emitter.
 *
 *  - Receiver case: a receiver is connected to only one active
 *    transmitter which can be either an emitter or a variant playing
 *    the role of an emitter. The returned variant comes from this
 *    active transmitter.
 *
 *  - Variant case: the variant transmitter can play the role of the
 *    emitter or the receiver. When acting as an emitter, the returned
 *    variant is the one that has been passed to this variant
 *    transmitter. Conversely, when acting as a receiver, the varaint
 *    transmitter is connected to only one active transmitter that is
 *    either an emitter or a variant. The returned variant then comes
 *    from this active transmitter.
 */
dtkComposerVariant& dtkComposerTransmitter::variant(void)
{
    return d->variant;
}

//! 
/*!  
 *  
 */
int dtkComposerTransmitter::type(void)
{
    return d->type;
}

// //! 
// /*!  
//  *  
//  */
// const dtkComposerType& dtkComposerTransmitter::dataType(void)
// {
//     return *d->data_type;
// }

// //! Returns the type name of the data transmitted by the transmitter.
// /*!  
//  *  
//  */
// QString dtkComposerTransmitter::dataIdentifier(void)
// {
//     return d->variant.identifier();
// }

// //! Returns a description of the data.
// /*!  
//  *  For atomic types, such as boolean, integer, double and QString,
//  *  the data value is returned.
//  *
//  *  For objects deriving from dtkAbstractObject, this method wraps the
//  *  description() method.
//  *
//  *  Otherwise, the address of the data is returned.
//  */
// QString dtkComposerTransmitter::dataDescription(void)
// {
//     return d->variant.description();
// }

// //! Returns the header of the data under ByteArray format.
// /*!  
//  *  This header varies the QMetaType index for 
//  */
// QByteArray dtkComposerTransmitter::dataHeader(void)
// {
//     QByteArray header;
//     QDataStream stream(&header, QIODevice::WriteOnly);

//     const dtkComposerVariant& v = this->variant();
//     qint64 type = v.userType();
    
//     stream << dtkComposerTypes->value(type, type) << v.identifier();

//     return header;
// }

//! Sets the node to which the current transmitter is parented.
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

    if (!active)
        return;

    foreach(dtkComposerTransmitter *receiver, d->receivers)
        receiver->activateEmitter(this);
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
void dtkComposerTransmitter::activateEmitter(dtkComposerTransmitter *emitter)
{
    DTK_UNUSED(emitter);
}

//! Returns true if transmitter is active.
/*! 
 *  Active flags is typically used to select an emitter among a list
 *  owned by a control node.
 */
void dtkComposerTransmitter::activateEmitter(dtkComposerTransmitterVariant *emitter)
{
    DTK_UNUSED(emitter);
}

//! Sets the type of data transmission.
/*! 
 *  The transmission type can be either AutoCopy, Copy, or
 *  Reference. By default, the transmission type is AutoCopy.
 *
 *  When AutoCopy is on, the receiver checks if it is the only one
 *  that receives the data. For that, it calls enableCopy() method. If
 *  false is returned, it means that it is the only receiver for this
 *  data and no copy is performed. Otherwise, in order to ensure that
 *  the received data has not be modified, a copy is carried out.
 *
 *  When Copy is on, the copy is enforced whatever the number of
 *  receivers for the same data.
 *
 *  When reference is on, no copy is carried out, the data is likely
 *  not the same that the one expected if another node has modified it
 *  before.
 */
void dtkComposerTransmitter::setDataTransmission(DataTransmission value)
{
    d->data_transmission = value;
}

//! Returns the type of the data transmission.
/*! 
 *  
 */
dtkComposerTransmitter::DataTransmission dtkComposerTransmitter::dataTransmission(void) const
{
    return d->data_transmission;
}

//! Returns true if more than one receiver is connected to one
//! emitter. Returns false otherwise.
/*! 
 *  Returns trgue by default.
 */
bool dtkComposerTransmitter::enableCopy(void)
{
    return true;
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

//! Adds \a receiver to the list of the receivers to which the current
//! transmitter is connected.
/*! 
 *  
 */
void dtkComposerTransmitter::appendReceiver(dtkComposerTransmitter *receiver)
{
    d->receivers << receiver;
}

//! Remove \a receiver from the list of the receivers to which the current
//! transmitter is connected.
/*! 
 *  
 */
void dtkComposerTransmitter::removeReceiver(dtkComposerTransmitter *receiver)
{
    d->receivers.removeAll(receiver);
}

//! Returns the number of receiver transmitters to which the current
//! transmitter is connected.
/*! 
 *  
 */
int dtkComposerTransmitter::receiverCount(void)
{
    return d->receivers.count();
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
    debug.nospace() << "dtkComposerTransmitter:" << transmitter.kindName() << const_cast<dtkComposerTransmitter&>(transmitter).dataIdentifier();
    
    return debug.space();
}

//!  Writes the transmitter's identifier to the stream.
/*! 
 *  
 */
QDebug operator<<(QDebug debug, dtkComposerTransmitter *transmitter)
{
    debug.nospace() << "dtkComposerTransmitter:" << transmitter->kindName() << transmitter->dataIdentifier();
    
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
