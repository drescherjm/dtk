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

#include "dtkComposerTransmitterAbstractEmitter.h"

#include <dtkContainer/dtkContainerVector.h>

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterEmitter interface
// /////////////////////////////////////////////////////////////////

template <typename T> class dtkComposerTransmitterEmitter : public dtkComposerTransmitterAbstractEmitter
{
public:
     dtkComposerTransmitterEmitter(dtkComposerNode *parent = 0);
    ~dtkComposerTransmitterEmitter(void);

public:
    void clearData(void);

public:
    inline void setData(      T& data);
    inline void setData(const T& data);

public:
    inline T& data(void);

public:
    inline Kind kind(void) const;

    inline QString kindName(void) const;

private:
    T m_data;

    using dtkComposerTransmitterAbstractEmitter::d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterEmitterVector interface
// /////////////////////////////////////////////////////////////////

template <typename T> class dtkComposerTransmitterEmitterVector : public dtkComposerTransmitterAbstractEmitter
{
public:
     dtkComposerTransmitterEmitterVector(dtkComposerNode *parent = 0);
    ~dtkComposerTransmitterEmitterVector(void);

public:
    void clearData(void);

public:
    inline void setData(dtkContainerVector<T> *vector);
    
    inline void setData(const dtkContainerVector<T> *vector);

public:
    inline dtkContainerVector<T> *data(void);

public:
    inline dtkComposerTransmitter::Kind kind(void) const;

    inline QString kindName(void) const;

private:
    dtkContainerVector<T> *m_vector;

    using dtkComposerTransmitterAbstractEmitter::d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterEmitter implementation
// /////////////////////////////////////////////////////////////////

#include "dtkComposerTransmitterEmitter.tpp"

#endif
