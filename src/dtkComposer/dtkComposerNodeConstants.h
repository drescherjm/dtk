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

#ifndef DTKCOMPOSERNODECONSTANTS_H
#define DTKCOMPOSERNODECONSTANTS_H

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

public:
    inline QString type(void) {
        return "pi";
    }

    inline QString titleHint(void) {
        return "Pi";
    }

    inline QString outputLabelHint(int) {
        return "value";
    }

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

public:
    inline QString type(void) {
        return "e";
    }

    inline QString titleHint(void) {
        return "E";
    }

    inline QString outputLabelHint(int) {
        return "value";
    }

private:
    dtkComposerNodeEPrivate *d;
};

#if defined(DTK_BUILD_DISTRIBUTED)

// /////////////////////////////////////////////////////////////////
// CONTROLLER_RUN_RANK
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeControllerRunRankPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeControllerRunRank : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeControllerRunRank(void);
    ~dtkComposerNodeControllerRunRank(void);

public:
    void run(void);

public:
    inline QString type(void) {
        return "ControllerRunRank";
    }

    inline QString titleHint(void) {
        return "CONTROLLER_RUN_RANK";
    }

    inline QString outputLabelHint(int) {
        return "value";
    }

private:
    dtkComposerNodeControllerRunRankPrivate *d;
};

#endif

#if defined(DTK_BUILD_DISTRIBUTED) && defined(DTK_HAVE_MPI)

// /////////////////////////////////////////////////////////////////
// MPI_ANY_TAG
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeMpiAnyTagPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeMpiAnyTag : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeMpiAnyTag(void);
    ~dtkComposerNodeMpiAnyTag(void);

public:
    void run(void);

public:
    inline QString type(void) {
        return "MpiAnyTag";
    }

    inline QString titleHint(void) {
        return "MPI_ANY_TAG";
    }

    inline QString outputLabelHint(int) {
        return "value";
    }

private:
    dtkComposerNodeMpiAnyTagPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// MPI_ANY_SOURCE
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeMpiAnySourcePrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeMpiAnySource : public dtkComposerNodeLeaf
{
public:
     dtkComposerNodeMpiAnySource(void);
    ~dtkComposerNodeMpiAnySource(void);

public:
    void run(void);

public:
    inline QString type(void) {
        return "MpiAnySource";
    }

    inline QString titleHint(void) {
        return "MPI_ANY_SOURCE";
    }

    inline QString outputLabelHint(int) {
        return "value";
    }

private:
    dtkComposerNodeMpiAnySourcePrivate *d;
};


#endif

#endif
