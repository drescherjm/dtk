/* dtkComposerTransmitterVariant.h --- 
 * 
 * Author: Thibaud Kloczko, Inria.
 * Created: Fri Mar  2 16:19:20 2012 (+0100)
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERTRANSMITTERVARIANT_H
#define DTKCOMPOSERTRANSMITTERVARIANT_H

#include <dtkConfig.h>

#include "dtkComposerTransmitter.h"

template <typename T> class dtkContainerVector;
template <typename T> class dtkComposerTransmitterVariantHandler;

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterVariant declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerTransmitterVariantPrivate;

class  dtkComposerTransmitterVariant : public dtkComposerTransmitter
{
public:
     dtkComposerTransmitterVariant(dtkComposerNode *parent = 0);
    ~dtkComposerTransmitterVariant(void);

public:
    void clearData(void);

public:
    template <typename T> inline void setData(T& data);
    template <typename T> inline void setData(const T& data);
    template <typename T> inline void setData(dtkContainerVector<T> *data);
    template <typename T> inline void setData(const dtkContainerVector<T> *data);

public:
    void setData(dtkAbstractContainerWrapper *data);

public:
    void setDataFrom(dtkComposerTransmitterVariant *source);

    void setDataFrom(QByteArray& array);

public:
    template <typename T> T      data(void);
    template <typename T> T constData(void);

public:
    template<typename T> friend class dtkComposerTransmitterVariantHandler;

public:
    QByteArray dataToByteArray(void);

public:
    dtkComposerVariant& variant(void);

    dtkAbstractContainerWrapper *containerFromEmitter(void);
    dtkAbstractContainerWrapper *container(void);

    const dtkAbstractContainerWrapper *constContainer(void);

public:
    const dtkComposerType& dataType(void);

    QString  dataIdentifier(void);
    QString dataDescription(void);

public:
    QVector<const dtkComposerType*> allDataType(void);

    QStringList  allDataIdentifier(void);
    QStringList allDataDescription(void);

public:
    void setActive(bool active);

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
    void setDataTypes(const QVector<const dtkComposerType*>& data_types);

    QVector<const dtkComposerType*> dataTypes(void);

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
