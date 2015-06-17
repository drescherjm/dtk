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

#pragma once

#include "dtkComposerExport.h"

#include "dtkComposerNodeLeaf.h"

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

protected:
    dtkComposerNodeCommunicatorSizePrivate *d;
};


// /////////////////////////////////////////////////////////////////
// Distributed communicator send Variant
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeCommunicatorSendPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeCommunicatorSend : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeCommunicatorSend(void);
    ~dtkComposerNodeCommunicatorSend(void);

public:
    void run(void);

protected:
    dtkComposerNodeCommunicatorSendPrivate *d;
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

protected:
    dtkComposerNodeCommunicatorReceivePrivate *d;
};

