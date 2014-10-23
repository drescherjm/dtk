/* dtkComposerTransmitterReceiver.h ---
 * 
 * Author: Thibaud Kloczko
 * Created: Thu Mar 21 10:41:02 2013 (+0100)
 * Version: 
 * Last-Updated: jeu. oct. 23 15:34:11 2014 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 96
 */

/* Change Log:
 * 
 */

#pragma once

#include "dtkComposerExport.h"

#include "dtkComposerTransmitter.h" 

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterReceiverBase
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerTransmitterReceiverBase : public dtkComposerTransmitter
{
public:
             dtkComposerTransmitterReceiverBase(dtkComposerNode *parent = 0);
    virtual ~dtkComposerTransmitterReceiverBase(void);

public:
    dtkComposerTransmitter::Kind kind(void) const;

    QString kindName(void) const;

public:
    inline bool enableCopy(void);

public:
    inline QVariant variant(void);

public:
    inline QVariantList allData(void);

public:
    bool    connect(dtkComposerTransmitter *transmitter);
    bool disconnect(dtkComposerTransmitter *transmitter);

public:
    LinkMap rightLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list);
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterReceiverVariant 
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerTransmitterReceiverVariant : public dtkComposerTransmitterReceiverBase
{
public:
     dtkComposerTransmitterReceiverVariant(dtkComposerNode *parent = 0);
    ~dtkComposerTransmitterReceiverVariant(void);

public:
    template <typename T> inline T      data(void);
    template <typename T> inline T constData(void);
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterReceiver 
// /////////////////////////////////////////////////////////////////

template <typename T> class dtkComposerTransmitterReceiver : public dtkComposerTransmitterReceiverBase
{
public:
     dtkComposerTransmitterReceiver(dtkComposerNode *parent = 0);
    ~dtkComposerTransmitterReceiver(void);

public:
    inline T      data(void);
    inline T constData(void);

public:
    inline int type(void) const;

private:
    void setTypeList(const TypeList& list) {;}

private:
    using dtkComposerTransmitterReceiverBase::d;
};

// ///////////////////////////////////////////////////////////////////
// Implementations
// ///////////////////////////////////////////////////////////////////

#include "dtkComposerTransmitterReceiver.tpp"
