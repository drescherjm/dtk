/* @(#)dtkComposerNodeDistributed.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/03/26 08:51:28
 * Version: $Id$
 * Last-Updated: jeu. janv. 17 15:54:56 2013 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 62
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERNODEDISTRIBUTED_H
#define DTKCOMPOSERNODEDISTRIBUTED_H

#include "dtkComposerSupportExport.h"
#include "dtkComposerNodeLeaf.h"

// /////////////////////////////////////////////////////////////////
// Distributed communicator init
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeCommunicatorInitPrivate;

class dtkComposerNodeCommunicatorInit : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeCommunicatorInit(void);
    ~dtkComposerNodeCommunicatorInit(void);

public:
    void run(void);

public:
    inline QString type(void) {
        return "communicatorInit";
    }

    inline QString titleHint(void) {
        return "Communicator Init";
    }

public:
    inline QString outputLabelHint(int) {
        return "value";
    }

protected:
    dtkComposerNodeCommunicatorInitPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// Distributed communicator uninitialize
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeCommunicatorUninitializePrivate;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeCommunicatorUninitialize : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeCommunicatorUninitialize(void);
    ~dtkComposerNodeCommunicatorUninitialize(void);

public:
    void run(void);

public:
    inline QString type(void) {
        return "communicatorUninitialize";
    }

    inline QString titleHint(void) {
        return "Communicator Uninitialize";
    }

public:
    inline QString outputLabelHint(int) {
        return "value";
    }

protected:
    dtkComposerNodeCommunicatorUninitializePrivate *d;
};



// /////////////////////////////////////////////////////////////////
// Distributed communicator rank
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeCommunicatorRankPrivate;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeCommunicatorRank : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeCommunicatorRank(void);
    ~dtkComposerNodeCommunicatorRank(void);

public:
    void run(void);

public:
    inline QString type(void) {
        return "communicatorRank";
    }

    inline QString titleHint(void) {
        return "CommunicatorRank";
    }

public:
    inline QString outputLabelHint(int) {
        return "value";
    }

protected:
    dtkComposerNodeCommunicatorRankPrivate *d;
};


// /////////////////////////////////////////////////////////////////
// Distributed communicator size
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeCommunicatorSizePrivate;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeCommunicatorSize : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeCommunicatorSize(void);
    ~dtkComposerNodeCommunicatorSize(void);

public:
    void run(void);

public:
    inline QString type(void) {
        return "communicatorSize";
    }

    inline QString titleHint(void) {
        return "Communicator Size";
    }

public:
    inline QString outputLabelHint(int) {
        return "value";
    }

protected:
    dtkComposerNodeCommunicatorSizePrivate *d;
};


// /////////////////////////////////////////////////////////////////
// Distributed communicator send Variant
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeCommunicatorSendPrivate;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeCommunicatorSend : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeCommunicatorSend(void);
    ~dtkComposerNodeCommunicatorSend(void);

public:
    void run(void);

public:
    inline QString type(void) {
        return "communicatorSend";
    }

    inline QString titleHint(void) {
        return "Communicator Send";
    }

public:
    inline QString inputLabelHint(int port) {
        if (port == 0)
            return "communicator";
        else if (port == 1)
            return "data";
        else if (port == 2)
            return "target rank";
        else if (port == 3)
            return "tag";
        else
            return "value";
    }

public:
    inline QString outputLabelHint(int) {
        return "communicator";
    }

protected:
    dtkComposerNodeCommunicatorSendPrivate *d;
};




// /////////////////////////////////////////////////////////////////
// Distributed communicator receive
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeCommunicatorReceivePrivate;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeCommunicatorReceive : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeCommunicatorReceive(void);
    ~dtkComposerNodeCommunicatorReceive(void);

public:
    void run(void);

public:
    inline QString type(void) {
        return "communicatorReceive";
    }

    inline QString titleHint(void) {
        return "Communicator Receive";
    }


public:
    inline QString inputLabelHint(int port) {
        if (port == 0)
            return "communicator";
        else if (port == 1)
            return "source rank";
        else if (port == 2)
            return "tag";
        else if (port == 3)
            return "data";
        else
            return "value";
    }

public:
    inline QString outputLabelHint(int port) {
        if (port == 0)
            return "data";
        else if (port == 1)
            return "source";
        else if (port == 2)
            return "tag";
        else
            return "value";
    }

protected:
    dtkComposerNodeCommunicatorReceivePrivate *d;
};



#endif /* DTKCOMPOSERNODEDISTRIBUTED_H */

