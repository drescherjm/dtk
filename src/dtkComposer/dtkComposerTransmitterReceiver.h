/* dtkComposerTransmitterReceiver.h --- 
 * 
 * Author: Thibaud Kloczko, Inria.
 * Created: Tue Feb 14 11:39:15 2012 (+0100)
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERTRANSMITTERRECEIVER_H
#define DTKCOMPOSERTRANSMITTERRECEIVER_H


#include "dtkComposerTransmitterAbstractReceiver.h"

#include <QtCore>

template <typename T> class dtkComposerTransmitterEmitter;
template <typename T, bool> class dtkComposerTransmitterEngine;

class dtkComposerTransmitterVariant;

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterReceiverBase interface
// /////////////////////////////////////////////////////////////////

template <typename T> class dtkComposerTransmitterReceiverBase : public dtkComposerTransmitterAbstractReceiver
{
public:
     dtkComposerTransmitterReceiverBase(dtkComposerNode *parent = 0);
    ~dtkComposerTransmitterReceiverBase(void);

public:
    void activateEmitter(dtkComposerTransmitter        *emitter);
    void activateEmitter(dtkComposerTransmitterVariant *emitter);

public:
    bool enableCopy(void);

public:
    bool isEmpty(void) const;

public:
    Kind kind(void) const;

    QString kindName(void) const;

public:
    bool    connect(dtkComposerTransmitter *transmitter);
    bool disconnect(dtkComposerTransmitter *transmitter);

protected:
    QList<dtkComposerTransmitterEmitter<T> *> emitters;
    QList<dtkComposerTransmitterVariant *>    variants;

protected:
    dtkComposerTransmitterEmitter<T> *active_emitter;
    dtkComposerTransmitterVariant    *active_variant;

protected:
    using dtkComposerTransmitterAbstractReceiver::d;
};


// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterReceiver interface
// /////////////////////////////////////////////////////////////////

template <typename T> class dtkComposerTransmitterReceiver : public dtkComposerTransmitterReceiverBase<T>
{
public:
     dtkComposerTransmitterReceiver(dtkComposerNode *parent = 0);
    ~dtkComposerTransmitterReceiver(void);

public:
    void clearData(void);

public:
    T& dataFromEmitter(void);

public:
    T&      data(void);
    T& constData(void);

public:
    dtkComposerVariant& variant(void);
          
    QVector<T> allData(void);

public:
    template <typename, bool> friend class dtkComposerTransmitterEngine;

private:
    T m_data;

    using dtkComposerTransmitterAbstractReceiver::d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterReceiver interface
// /////////////////////////////////////////////////////////////////

template <typename T> class dtkComposerTransmitterReceiver<T*> : public dtkComposerTransmitterReceiverBase<T*>
{
public:
     dtkComposerTransmitterReceiver(dtkComposerNode *parent = 0);
    ~dtkComposerTransmitterReceiver(void);

public:
    void clearData(void);

public:
    T* dataFromEmitter(void);

public:
    T*      data(void);
    T* constData(void);

public:
    dtkComposerVariant& variant(void);
          
    QVector<T*> allData(void);

public:
    template <typename, bool> friend class dtkComposerTransmitterEngine;

private:
    T* m_data;

    using dtkComposerTransmitterAbstractReceiver::d;
};

// /////////////////////////////////////////////////////////////////

#include <dtkContainer/dtkContainerVector.h>

template <typename T> class dtkComposerTransmitterEmitterVector;

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterReceiverVector interface
// /////////////////////////////////////////////////////////////////

template <typename T> class dtkComposerTransmitterReceiverVector : public dtkComposerTransmitterAbstractReceiver
{
public:
     dtkComposerTransmitterReceiverVector(dtkComposerNode *parent = 0);
    ~dtkComposerTransmitterReceiverVector(void);

public:
    void clearData(void);

public:
    dtkContainerVector<T> *dataFromEmitter(void);

public:
    dtkContainerVector<T>      *data(void);
    dtkContainerVector<T> *constData(void);

public:
    dtkAbstractContainerWrapper *container(void);

    dtkComposerVariant& variant(void);

public:
    void activateEmitter(dtkComposerTransmitter        *emitter);
    void activateEmitter(dtkComposerTransmitterVariant *emitter);

public:
    bool enableCopy(void);

public:
    bool isEmpty(void) const;

public:
    Kind kind(void) const;

    QString kindName(void) const;

public:
    bool    connect(dtkComposerTransmitter *transmitter);
    bool disconnect(dtkComposerTransmitter *transmitter);

private:
    QList<dtkComposerTransmitterEmitterVector<T> *> emitters;
    QList<dtkComposerTransmitterVariant *>          variants;

private:
    dtkComposerTransmitterEmitterVector<T> *active_emitter;
    dtkComposerTransmitterVariant          *active_variant;

private:
    dtkContainerVector<T> *m_vector;

    using dtkComposerTransmitterAbstractReceiver::d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterReceiver implementation
// /////////////////////////////////////////////////////////////////

#include "dtkComposerTransmitterReceiver.tpp"

#endif
