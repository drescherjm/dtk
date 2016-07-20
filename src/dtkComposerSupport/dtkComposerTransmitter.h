/* dtkComposerTransmitter.h ---
 *
 * Author: Thibaud Kloczko, Inria.
 * Created: Mon Jan 30 16:36:09 2012 (+0100)
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERTRANSMITTER_H
#define DTKCOMPOSERTRANSMITTER_H

#include "dtkComposerSupportExport.h"
#include "dtkComposerMetatype.h"

#include <QtCore>

class dtkAbstractObject;
class dtkAbstractContainerWrapper;
class dtkComposerNode;
class dtkComposerTransmitterPrivate;
class dtkComposerTransmitterLink;
class dtkComposerTransmitterLinkList;
class dtkComposerTransmitterVariant;
namespace dtkDeprecated {
    template <typename T> class dtkMatrix;
}

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitter interface
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerTransmitter
{
public:
    enum Kind {
        Emitter,
        Receiver,
        Proxy,
        Variant,
        EmitterVector,
        ReceiverVector
    };

public:
    enum DataTransmission {
        AutoCopy,
        Copy,
        Reference
    };

public:
    dtkComposerTransmitter(dtkComposerNode *parent = 0);
    virtual ~dtkComposerTransmitter(void);

public:
    virtual void clearData(void);

public:
    virtual Kind kind(void) const = 0;

    virtual QString kindName(void) const = 0;

public:
    virtual QVariant& variant(void);

public:
    virtual dtkAbstractObject *object(void);

public:
    virtual dtkDeprecated::dtkMatrix<double> *matrix(void);

public:
    virtual dtkAbstractContainerWrapper *container(void);

public:
    virtual int dataType(void);

    virtual QString  dataIdentifier(void);
    virtual QString dataDescription(void);

public:
    void setParentNode(dtkComposerNode *parent);

    dtkComposerNode *parentNode(void) const;

public:
    virtual void setActive(bool active);

    bool active(void);

public:
    virtual void activateEmitter(dtkComposerTransmitter        *emitter);
    virtual void activateEmitter(dtkComposerTransmitterVariant *emitter);

public:
    virtual void setReady(bool ready);

public:
    void updateCopyCounter(bool value);
    bool copyCounterIsGreaterThanOne(void);

public:
    void setDataTransmission(DataTransmission value);

    DataTransmission dataTransmission(void) const;

    virtual bool enableCopy(void);

public:
    void setRequired(bool required);

    bool required(void);

public:
    void appendNext(dtkComposerTransmitter *transmitter);
    void removeNext(dtkComposerTransmitter *transmitter);

    void appendPrevious(dtkComposerTransmitter *transmitter);
    void removePrevious(dtkComposerTransmitter *transmitter);

public:
    virtual bool    connect(dtkComposerTransmitter *transmitter);
    virtual bool disconnect(dtkComposerTransmitter *transmitter);

public:
    void appendReceiver(dtkComposerTransmitter *receiver);
    void removeReceiver(dtkComposerTransmitter *receiver);

public:
    int receiverCount(void);

#pragma mark -
#pragma mark Link management

public:
    typedef QMultiHash<dtkComposerTransmitter *, dtkComposerTransmitterLink *> LinkMap;

public:
    virtual LinkMap  leftLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list);
    virtual LinkMap rightLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list);

public:
    static bool onTransmittersConnected(dtkComposerTransmitter *source, dtkComposerTransmitter *destination, dtkComposerTransmitterLinkList& valid_links, dtkComposerTransmitterLinkList& invalid_links);
    static bool onTransmittersDisconnected(dtkComposerTransmitter *source, dtkComposerTransmitter *destination, dtkComposerTransmitterLinkList& invalid_links);

protected:
    dtkComposerTransmitterPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// Debug operators
// /////////////////////////////////////////////////////////////////

DTKCOMPOSERSUPPORT_EXPORT QDebug operator<<(QDebug debug, const dtkComposerTransmitter& transmitter);
DTKCOMPOSERSUPPORT_EXPORT QDebug operator<<(QDebug debug,       dtkComposerTransmitter *transmitter);

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterLink declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerTransmitterLinkPrivate;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerTransmitterLink
{
public:
    dtkComposerTransmitterLink(dtkComposerTransmitter *source, dtkComposerTransmitter *destination);
    ~dtkComposerTransmitterLink(void);

public:
    dtkComposerTransmitter *source();
    dtkComposerTransmitter *destination();

private:
    dtkComposerTransmitterLinkPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterLinkList declaration
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerTransmitterLinkList : public QList<dtkComposerTransmitterLink *> {};

#endif
