/* dtkComposerTransmitterVariant.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Fri Mar  2 16:19:20 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Sep 18 10:28:18 2012 (+0200)
 *           By: tkloczko
 *     Update #: 151
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERTRANSMITTERVARIANT_H
#define DTKCOMPOSERTRANSMITTERVARIANT_H

#include "dtkComposerExport.h"
#include "dtkComposerTransmitter.h"

#include <dtkCore/dtkGlobal>

template <typename T> class dtkContainerVector;

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterVariant declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerTransmitterVariantPrivate;
class dtkDistributedMessage;

class DTKCOMPOSER_EXPORT dtkComposerTransmitterVariant : public dtkComposerTransmitter
{
public:
     dtkComposerTransmitterVariant(dtkComposerNode *parent = 0);
    ~dtkComposerTransmitterVariant(void);

public:
    template <typename T> inline void setData(T *data);
    template <typename T> inline void setData(dtkContainerVector<T> *data);

public:
    void setData(const QVariant& data);
    void setData(dtkAbstractContainerWrapper *data);

public:
    void setDataFrom(dtkComposerTransmitterVariant *source);
    void setDataFrom(dtkDistributedMessage *msg);

public:
    template <typename T> T *data(void);

public:
    int dataType(void);

    QString dataDescription(void);

public:
    QVariant& variant(void);

    dtkAbstractContainerWrapper *containerFromEmitter(void);
    dtkAbstractContainerWrapper *container(void);

    QVariantList allData(void);

public:
    void activateEmitter(dtkComposerTransmitter        *emitter);
    void activateEmitter(dtkComposerTransmitterVariant *emitter);

public:
    bool enableCopy(void);

    void reset(void);

public:
    bool isEmpty(void) const;

public:
    void setTwin(dtkComposerTransmitterVariant *twin);

    dtkComposerTransmitterVariant *twin(void);
    
    void setTwinned(bool twinned);

public:
    Kind kind(void) const;

    QString kindName(void) const;

public:
    void setTypes(QList<QVariant::Type> types);

    QList<QVariant::Type> types(void);

public:
    bool    connect(dtkComposerTransmitter *transmitter);
    bool disconnect(dtkComposerTransmitter *transmitter);

public:
    LinkMap  leftLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list);
    LinkMap rightLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list);

protected:
    dtkComposerTransmitterVariantPrivate *e;
};

#include "dtkComposerTransmitterVariant.tpp"

#endif
