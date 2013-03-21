/* dtkComposerTransmitterReceiver.h ---
 * 
 * Author: Thibaud Kloczko
 * Created: Thu Mar 21 10:41:02 2013 (+0100)
 * Version: 
 * Last-Updated: Thu Mar 21 14:41:02 2013 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 51
 */

/* Change Log:
 * 
 */

#pragma once

#include <QtCore>

template <typename T> class dtkComposerTransmitterEmitter;
class dtkComposerTransmitterVariant;

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterReceiverBase
// /////////////////////////////////////////////////////////////////

class dtkComposerTransmitterReceiverBase : public dtkComposerTransmitter
{
public:
     dtkComposerTransmitterReceiverBase(dtkComposerNode *parent = 0);
    ~dtkComposerTransmitterReceiverBase(void);

public:
    inline void activateEmitter(dtkComposerTransmitter *emitter);

public:
    inline void clearData(void);

public:
    inline bool enableCopy(void);

public:
    inline bool isEmpty(void) const;

public:
    inline QVariant& variant(void);

public:
    inline QVariantList allData(void);

public:
    bool    connect(dtkComposerTransmitter *transmitter);
    bool disconnect(dtkComposerTransmitter *transmitter);

protected:
    QList<dtkComposerTransmitter *> emitters;

protected:
    dtkComposerTransmitter *active_emitter;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterReceiver interface
// /////////////////////////////////////////////////////////////////

template <typename T> class dtkComposerTransmitterReceiver : public dtkComposerTransmitterReceiverBase
{
public:
     dtkComposerTransmitterReceiver(dtkComposerNode *parent = 0);
    ~dtkComposerTransmitterReceiver(void);

public:
    dtkComposerTransmitter::Kind kind(void) const;

    QString kindName(void) const;

public:
    inline T      data(void);
    inline T constData(void);

private:
    using dtkComposerTransmitterAbstractReceiver::d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterReceiver interface
// /////////////////////////////////////////////////////////////////

template <typename T> class dtkComposerTransmitterReceiver<T*> : public dtkComposerTransmitterReceiverBase
{
public:
     dtkComposerTransmitterReceiver(dtkComposerNode *parent = 0);
    ~dtkComposerTransmitterReceiver(void);

public:
    dtkComposerTransmitter::Kind kind(void) const;

    QString kindName(void) const;

public:
    inline T*      data(void);
    inline T* constData(void);

private:
    using dtkComposerTransmitterAbstractReceiver::d;
};

// ///////////////////////////////////////////////////////////////////
// Implementations
// ///////////////////////////////////////////////////////////////////

#include "dtkComposerTransmitterReceiver.tpp"
