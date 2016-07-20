/* @(#)dtkComposerNodeExec.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2014 - Nicolas Niclausse, Inria.
 * Created: 2014/05/19 08:21:48
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

class dtkComposerNodeExecPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeExec : public dtkComposerNodeLeaf
{
public:
    dtkComposerNodeExec(void);
    ~dtkComposerNodeExec(void);

public:
    void run(void);

private:
    dtkComposerNodeExecPrivate *d;
};




