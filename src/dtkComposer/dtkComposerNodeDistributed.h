/* @(#)dtkComposerNodeDistributed.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/03/26 08:51:28
 * Version: $Id$
 * Last-Updated: jeu. mars 29 23:02:08 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 50
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERNODEDISTRIBUTED_H
#define DTKCOMPOSERNODEDISTRIBUTED_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeLeaf.h"

// /////////////////////////////////////////////////////////////////
// Distributed communicator init
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeCommunicatorInitPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeCommunicatorInit : public dtkComposerNodeLeaf
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

class DTKCOMPOSER_EXPORT dtkComposerNodeCommunicatorUninitialize : public dtkComposerNodeLeaf
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

class DTKCOMPOSER_EXPORT dtkComposerNodeCommunicatorRank : public dtkComposerNodeLeaf
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

class DTKCOMPOSER_EXPORT dtkComposerNodeCommunicatorSize : public dtkComposerNodeLeaf
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
// Distributed communicator send Integer
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeCommunicatorSendIntegerPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeCommunicatorSendInteger : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeCommunicatorSendInteger(void);
    ~dtkComposerNodeCommunicatorSendInteger(void);

public:
    void run(void);

public:
    inline QString type(void) {
        return "communicatorSendInteger";
    }

    inline QString titleHint(void) {
        return "Communicator SendInteger";
    }

public:
    inline QString inputLabelHint(int port) {
        if (port == 0)
            return "communicator";
        else if (port == 1)
            return "data";
        else if (port == 2)
            return "target rank";
        else
            return "value";
    }

public:
    inline QString outputLabelHint(int) {
        return "value";
    }

protected:
    dtkComposerNodeCommunicatorSendIntegerPrivate *d;
};


// /////////////////////////////////////////////////////////////////
// Distributed communicator send Real
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeCommunicatorSendRealPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeCommunicatorSendReal : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeCommunicatorSendReal(void);
    ~dtkComposerNodeCommunicatorSendReal(void);

public:
    void run(void);

public:
    inline QString type(void) {
        return "communicatorSendReal";
    }

    inline QString titleHint(void) {
        return "Communicator SendReal";
    }

public:
    inline QString inputLabelHint(int port) {
        if (port == 0)
            return "communicator";
        else if (port == 1)
            return "data";
        else if (port == 2)
            return "target rank";
        else
            return "value";
    }

public:
    inline QString outputLabelHint(int) {
        return "value";
    }

protected:
    dtkComposerNodeCommunicatorSendRealPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// Distributed communicator send dtkAbstractData
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeCommunicatorSendPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeCommunicatorSend : public dtkComposerNodeLeaf
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
        else
            return "value";
    }

public:
    inline QString outputLabelHint(int) {
        return "value";
    }

protected:
    dtkComposerNodeCommunicatorSendPrivate *d;
};


// /////////////////////////////////////////////////////////////////
// Distributed communicator receive Integer
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeCommunicatorReceiveIntegerPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeCommunicatorReceiveInteger : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeCommunicatorReceiveInteger(void);
    ~dtkComposerNodeCommunicatorReceiveInteger(void);

public:
    void run(void);

public:
    inline QString type(void) {
        return "communicatorReceiveInteger";
    }

    inline QString titleHint(void) {
        return "Communicator ReceiveInteger";
    }


public:
    inline QString inputLabelHint(int port) {
        if (port == 0)
            return "communicator";
        else if (port == 1)
            return "source rank";
        else
            return "value";
    }

public:
    inline QString outputLabelHint(int) {
        return "value";
    }

protected:
    dtkComposerNodeCommunicatorReceiveIntegerPrivate *d;
};


// /////////////////////////////////////////////////////////////////
// Distributed communicator receive Real
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeCommunicatorReceiveRealPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeCommunicatorReceiveReal : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeCommunicatorReceiveReal(void);
    ~dtkComposerNodeCommunicatorReceiveReal(void);

public:
    void run(void);

public:
    inline QString type(void) {
        return "communicatorReceiveReal";
    }

    inline QString titleHint(void) {
        return "Communicator ReceiveReal";
    }


public:
    inline QString inputLabelHint(int port) {
        if (port == 0)
            return "communicator";
        else if (port == 1)
            return "source rank";
        else
            return "value";
    }

public:
    inline QString outputLabelHint(int) {
        return "value";
    }

protected:
    dtkComposerNodeCommunicatorReceiveRealPrivate *d;
};



// /////////////////////////////////////////////////////////////////
// Distributed communicator receive 
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeCommunicatorReceivePrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeCommunicatorReceive : public dtkComposerNodeLeaf
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
        else
            return "value";
    }

public:
    inline QString outputLabelHint(int) {
        return "value";
    }

protected:
    dtkComposerNodeCommunicatorReceivePrivate *d;
};



#endif /* DTKCOMPOSERNODEDISTRIBUTED_H */

