/* dtkComposerNodeMetaScalarArray.h ---
 *
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Fri Jul 13 16:04:11 2012 (+0200)
 * Version: $Id$
 * Last-Updated: mar. févr.  4 15:22:12 2014 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 8
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERNODEMETASCALARARRAY_H
#define DTKCOMPOSERNODEMETASCALARARRAY_H

#include "dtkComposerSupportExport.h"

#include "dtkComposerNodeLeaf.h"

class dtkComposerNodeMetaScalarArrayPrivate;

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMetaScalarArray interface
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeMetaScalarArray : public dtkComposerNodeLeaf
{
public:
    dtkComposerNodeMetaScalarArray(void);
    ~dtkComposerNodeMetaScalarArray(void);

public:
    void run(void);

public:
    inline QString type(void) {
        return "meta_scalar_array";
    }

    inline QString titleHint(void) {
        return "Meta Scalar Array";
    }

public:
    QString outputLabelHint(int port);

private:
    dtkComposerNodeMetaScalarArrayPrivate *d;
};

#endif

