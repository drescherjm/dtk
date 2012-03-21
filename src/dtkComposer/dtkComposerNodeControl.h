/* dtkComposerNodeControl.h --- 
 * 
 * Author: David Rey
 * Copyright (C) 2008-2011 - David Rey, Inria.
 * Created: Tue Feb 14 15:40:03 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Mar 21 09:18:51 2012 (+0100)
 *           By: tkloczko
 *     Update #: 41
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODECONTROL_H
#define DTKCOMPOSERNODECONTROL_H

#include "dtkComposerExport.h"
#include "dtkComposerNode.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControl declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeLeaf;
class dtkComposerNodeComposite;
class dtkComposerNodeControlPrivate;

class dtkComposerTransmitterVariant;

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
    void appendInputTwin(dtkComposerTransmitterVariant *twin);
    void removeInputTwin(dtkComposerTransmitterVariant *twin);

    void appendOutputTwin(dtkComposerTransmitterVariant *twin);
    void removeOutputTwin(dtkComposerTransmitterVariant *twin);

    QList<dtkComposerTransmitterVariant *>  inputTwins(void);
    QList<dtkComposerTransmitterVariant *> outputTwins(void);

public:
    virtual void setInputs(void);
    virtual void setConditions(void);
    virtual void setOutputs(void);
    virtual void setVariables(void);
    virtual  int selectBranch(void);
    virtual void begin(void);
    virtual void end(void);

private:
    dtkComposerNodeControlPrivate *d;
};

#endif
