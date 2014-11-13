/* dtkComposerTransmitterProxyLoop.h ---
 * 
 * Author: Thibaud Kloczko
 * Created: Fri Mar 29 14:54:14 2013 (+0100)
 * Version: 
 * Last-Updated: jeu. nov. 13 09:19:44 2014 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 45
 */

/* Change Log:
 * 
 */

#pragma once

#include "dtkComposerExport.h"

#include "dtkComposerTransmitter.h"

// ///////////////////////////////////////////////////////////////////
// dtkComposerTransmitterProxyLoop
// ///////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerTransmitterProxyLoop : public dtkComposerTransmitter
{
public:
     dtkComposerTransmitterProxyLoop(dtkComposerNode *parent = 0);
    ~dtkComposerTransmitterProxyLoop(void);

public:
    dtkComposerTransmitter::Kind kind(void) const;

    QString kindName(void) const;

public:
    inline bool enableCopy(void);

public:
    inline QVariant variant(void);
    void setVariant(const QVariant&);

public:
    inline QVariantList allData(void);

public:
    inline void  enableLoopMode(void);
    inline void disableLoopMode(void);

public:
    inline void setTwin(dtkComposerTransmitterProxyLoop *twin);

    inline dtkComposerTransmitterProxyLoop *twin(void) const;

public:
    bool    connect(dtkComposerTransmitter *transmitter);
    bool disconnect(dtkComposerTransmitter *transmitter);

    bool enableConnection(dtkComposerTransmitter *transmitter);

public:
    LinkMap  leftLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list);
    LinkMap rightLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list);

private:
    void setTypeList(const TypeList& list) {;}

private:
    dtkComposerTransmitter *m_source;
    dtkComposerTransmitterProxyLoop *m_twin;
};

// ///////////////////////////////////////////////////////////////////
// Implementations
// ///////////////////////////////////////////////////////////////////

#include "dtkComposerTransmitterProxyLoop.tpp"
