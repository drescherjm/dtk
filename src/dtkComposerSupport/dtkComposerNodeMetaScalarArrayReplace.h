/* dtkComposerNodeMetaScalarArrayReplace.h ---
 *
 * Author: Régis Duvigneau
 * Copyright (C) 2008 - Regis Duvigneau, Inria.
 * Created: Thu Jul 19 10:27:53 2012 (+0200)
 * Version: $Id$
 * Last-Updated: mar. févr.  4 15:46:42 2014 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 3
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once
#define DTKCOMPOSERNODEMETASCALARARRAYREPLACE_H

#include "dtkComposerSupportExport.h"

#include "dtkComposerNodeLeaf.h"

class dtkComposerNodeMetaScalarArrayReplacePrivate;

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeMetaScalarArrayReplace interface
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeMetaScalarArrayReplace : public dtkComposerNodeLeaf
{
public:
    dtkComposerNodeMetaScalarArrayReplace(void);
    ~dtkComposerNodeMetaScalarArrayReplace(void);

public:
    void run(void);

public:
    inline QString type(void) {
        return "meta_scalar_array_replace";
    }

    inline QString titleHint(void) {
        return "Meta Scalar Array Replace";
    }

public:
    inline QString inputLabelHint(int port) {

        if (port == 0)
            return "arrays";

        if (port == 1)
            return "vector";

        if (port == 2)
            return "index";

        return "input";
    }

    inline QString outputLabelHint(int port) {

        if (port == 0)
            return "arrays";

        return "output";
    }

private:
    dtkComposerNodeMetaScalarArrayReplacePrivate *d;
};


