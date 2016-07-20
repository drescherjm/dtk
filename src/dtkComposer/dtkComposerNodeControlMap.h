/* dtkComposerNodeControlMap.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: lun. juin 18 16:08:06 2012 (+0100)
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include "dtkComposerExport.h"

#include "dtkComposerNodeControl.h"

class dtkComposerNodeControlMapPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeControlMap : public dtkComposerNodeControl
{
public:
    dtkComposerNodeControlMap(void);
    virtual ~dtkComposerNodeControlMap(void);

public:
    int blockCount(void);
    dtkComposerNodeLeaf *header(void);
    dtkComposerNodeLeaf *footer(void);
    dtkComposerNodeComposite *block(int id);

public:
    void setInputs(void);
    void setOutputs(void);
    void setVariables(void);
    int selectBranch(void);
    void begin(void);
    void end(void);

private:
    dtkComposerNodeControlMapPrivate *d;
};

