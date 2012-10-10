/* dtkComposerTransmitterEmitter.h --- 
 * 
 * Author: Thibaud Kloczko, Inria.
 * Created: Tue Feb 14 10:33:49 2012 (+0100)
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERTRANSMITTEREMITTER_H
#define DTKCOMPOSERTRANSMITTEREMITTER_H

#include "dtkComposerExport.h"
#include "dtkComposerTransmitter.h"

#include <dtkCore/dtkGlobal>

#include <dtkContainer/dtkContainerVector.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterEmitter interface
// /////////////////////////////////////////////////////////////////

template <typename T> class dtkComposerTransmitterEmitter : public dtkComposerTransmitter
{
public:
     dtkComposerTransmitterEmitter(dtkComposerNode *parent = 0);
    ~dtkComposerTransmitterEmitter(void);

public:
    void clearData(void);

public:
    inline void setData(T *data);

    inline T *data(void);

public:
    dtkAbstractObject *object(void);

public:
    dtkMatrix<double> *matrix(void);

public:
    virtual int dataType(void);

    virtual QString  dataIdentifier(void);
    virtual QString dataDescription(void);

public:
    virtual bool enableCopy(void);

public:
    virtual Kind kind(void) const;

    virtual QString kindName(void) const;

public:
    LinkMap leftLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list);

private:
    T *m_data;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterEmitterVector interface
// /////////////////////////////////////////////////////////////////

template <typename T> class dtkComposerTransmitterEmitterVector : public dtkComposerTransmitterEmitter<T>
{
public:
     dtkComposerTransmitterEmitterVector(dtkComposerNode *parent = 0);
    ~dtkComposerTransmitterEmitterVector(void);

public:
    void clearData(void);

public:
    inline void setData(dtkContainerVector<T> *vector);

    inline dtkContainerVector<T> *data(void);

public:
    dtkAbstractObject *object(void);

public:
    int dataType(void);

    QString  dataIdentifier(void);
    QString dataDescription(void);

public:
    bool enableCopy(void);

public:
    dtkComposerTransmitter::Kind kind(void) const;

    QString kindName(void) const;

private:
    dtkContainerVector<T> *m_vector;

    using dtkComposerTransmitterEmitter<T>::d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterEmitter implementation
// /////////////////////////////////////////////////////////////////

#include "dtkComposerTransmitterEmitter.tpp"

#endif
