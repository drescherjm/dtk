/* dtkComposerNodeConstants.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Feb 27 12:58:13 2012 (+0100)
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include <dtkConfig.h>

#include "dtkComposerExport.h"

#include "dtkComposerNodeLeaf.h"

// /////////////////////////////////////////////////////////////////
// PI
// /////////////////////////////////////////////////////////////////

class dtkComposerNodePiPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodePi : public dtkComposerNodeLeaf
{
public:
    dtkComposerNodePi(void);
    ~dtkComposerNodePi(void);

public:
    void run(void);

private:
    dtkComposerNodePiPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// E
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeEPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeE : public dtkComposerNodeLeaf
{
public:
    dtkComposerNodeE(void);
    ~dtkComposerNodeE(void);

public:
    void run(void);

private:
    dtkComposerNodeEPrivate *d;
};


#if defined(DTK_BUILD_DISTRIBUTED)

// /////////////////////////////////////////////////////////////////
// CONTROLLER_RUN_RANK
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeControllerRankPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeControllerRank : public dtkComposerNodeLeaf
{
public:
    dtkComposerNodeControllerRank(void);
    ~dtkComposerNodeControllerRank(void);

public:
    void run(void);

private:
    dtkComposerNodeControllerRankPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// MPI_ANY_TAG
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeAnyTagPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeAnyTag : public dtkComposerNodeLeaf
{
public:
    dtkComposerNodeAnyTag(void);
    ~dtkComposerNodeAnyTag(void);

public:
    void run(void);

private:
    dtkComposerNodeAnyTagPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// MPI_ANY_SOURCE
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeAnySourcePrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeAnySource : public dtkComposerNodeLeaf
{
public:
    dtkComposerNodeAnySource(void);
    ~dtkComposerNodeAnySource(void);

public:
    void run(void);

private:
    dtkComposerNodeAnySourcePrivate *d;
};


#endif
