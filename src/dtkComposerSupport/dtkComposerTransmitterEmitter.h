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

#include "dtkComposerSupportExport.h"
#include "dtkComposerTransmitterAbstractEmitter.h"

#include <dtkCoreSupport/dtkGlobal>
#include <dtkContainerSupport/dtkContainerVector.h>

namespace dtkDeprecated {
    template <typename T> class dtkMatrix;
}

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
    inline void setData(T *data);

    inline void setData(const T *data);

public:
    inline T *data(void);

public:
    dtkAbstractObject *object(void);

public:
    dtkDeprecated::dtkMatrix<double> *matrix(void);

public:
    virtual int dataType(void);

    virtual QString  dataIdentifier(void);
    virtual QString dataDescription(void);

public:
    virtual Kind kind(void) const;

    virtual QString kindName(void) const;

private:
    T *m_data;

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
    dtkAbstractObject *object(void);

public:
    int dataType(void);

    QString  dataIdentifier(void);
    QString dataDescription(void);

public:
    dtkComposerTransmitter::Kind kind(void) const;

    QString kindName(void) const;

private:
    dtkContainerVector<T> *m_vector;

    using dtkComposerTransmitterAbstractEmitter::d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterEmitter implementation
// /////////////////////////////////////////////////////////////////

#include "dtkComposerTransmitterEmitter.tpp"

#endif
