/* dtkComposerNodeControlDoWhile.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Feb 24 16:52:08 2012 (+0100)
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

class dtkComposerNodeControlDoWhilePrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeControlDoWhile : public dtkComposerNodeControl
{
public:
     dtkComposerNodeControlDoWhile(void);
    ~dtkComposerNodeControlDoWhile(void);

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
    dtkComposerNodeControlDoWhilePrivate *d;
};

