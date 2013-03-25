/* dtkComposerTransmitterVariant.h ---
 * 
 * Author: Thibaud Kloczko
 * Created: Fri Mar 22 09:12:57 2013 (+0100)
 * Version: 
 * Last-Updated: Mon Mar 25 09:24:02 2013 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 90
 */

/* Change Log:
 * 
 */

#pragma once

#include "dtkComposerTransmitter.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterVariant 
// /////////////////////////////////////////////////////////////////

class  dtkComposerTransmitterVariant : public dtkComposerTransmitter
{
public:
     dtkComposerTransmitterVariant(dtkComposerNode *parent = 0);
    ~dtkComposerTransmitterVariant(void);

public:
    Kind kind(void) const;

    QString kindName(void) const;

public:
    bool enableCopy(void);

public:
    QVariant variant(void);

public:
    void setTwin(dtkComposerTransmitterVariant *twin) {;}
    dtkComposerTransmitterVariant *twin() { return NULL; }

public:
    template <typename T> inline void setData(      T& data);
    template <typename T> inline void setData(const T& data);

public:
    template <typename T> inline T      data(void);
    template <typename T> inline T constData(void);

public:
    bool    connect(dtkComposerTransmitter *transmitter);
    bool disconnect(dtkComposerTransmitter *transmitter);

public:
    LinkMap  leftLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list);
    LinkMap rightLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list);

};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterVariant 
// /////////////////////////////////////////////////////////////////

#include "dtkComposerTransmitterVariant.tpp"
