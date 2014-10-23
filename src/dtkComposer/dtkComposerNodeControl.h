/* dtkComposerNodeControl.h --- 
 * 
 * Author: David Rey
 * Copyright (C) 2008-2011 - David Rey, Inria.
 * Created: Tue Feb 14 15:40:03 2012 (+0100)
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#pragma once

#include "dtkComposerExport.h"

#include "dtkComposerNode.h"

class dtkComposerNodeLeaf;
class dtkComposerNodeComposite;
class dtkComposerNodeControlPrivate;
class dtkComposerTransmitterProxyLoop;

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControl 
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSER_EXPORT dtkComposerNodeControl : public dtkComposerNode
{
public:
             dtkComposerNodeControl(void);
    virtual ~dtkComposerNodeControl(void);

public:
    virtual int blockCount(void) = 0;
    virtual dtkComposerNodeLeaf *header(void) = 0;
    virtual dtkComposerNodeLeaf *footer(void) = 0;
    virtual dtkComposerNodeComposite *block(int id) = 0;

public:
    void appendInputTwin(dtkComposerTransmitterProxyLoop *twin);
    void removeInputTwin(dtkComposerTransmitterProxyLoop *twin);

    void appendOutputTwin(dtkComposerTransmitterProxyLoop *twin);
    void removeOutputTwin(dtkComposerTransmitterProxyLoop *twin);

    QList<dtkComposerTransmitterProxyLoop *>  inputTwins(void);
    QList<dtkComposerTransmitterProxyLoop *> outputTwins(void);

public:
    virtual void setInputs(void);
    virtual void setOutputs(void);
    virtual void setVariables(void);
    virtual  int selectBranch(void);
    virtual void begin(void);
    virtual void end(void);

private:
    dtkComposerNodeControlPrivate *d;
};

