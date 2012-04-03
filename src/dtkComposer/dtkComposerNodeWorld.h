/* @(#)dtkComposerNodeWorld.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/04/03 12:58:15
 * Version: $Id$
 * Last-Updated: mar. avril  3 15:55:25 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 14
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERNODEWORLD_H
#define DTKCOMPOSERNODEWORLD_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeComposite.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeWorld declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeWorldPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeWorld : public dtkComposerNodeComposite
{
public:
             dtkComposerNodeWorld(void);
    virtual ~dtkComposerNodeWorld(void);

public:
    QString type(void);

public:
    QString titleHint(void);

public:
    virtual void begin(void);
    virtual void end(void);

private:
    dtkComposerNodeWorldPrivate *d;
};



// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMpiWorld declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeMpiWorldPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeMpiWorld : public dtkComposerNodeWorld
{
public:
             dtkComposerNodeMpiWorld(void);
    virtual ~dtkComposerNodeMpiWorld(void);

public:
    QString type(void);

public:
    QString titleHint(void);

public:
    void begin(void);
    void end(void);

private:
    dtkComposerNodeMpiWorldPrivate *d;
};

#endif /* DTKCOMPOSERNODEWORLD_H */

