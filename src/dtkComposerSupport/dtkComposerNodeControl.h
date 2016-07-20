/* dtkComposerNodeControl.h ---
 *
 * Author: David Rey
 * Copyright (C) 2008-2011 - David Rey, Inria.
 * Created: Tue Feb 14 15:40:03 2012 (+0100)
 * Version: $Id$
 * Last-Updated: mer. mars 28 13:58:44 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 42
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERNODECONTROL_H
#define DTKCOMPOSERNODECONTROL_H

#include "dtkComposerSupportExport.h"
#include "dtkComposerNode.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControl declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeLeaf;
class dtkComposerNodeComposite;
class dtkComposerNodeControlPrivate;

class dtkComposerTransmitterVariant;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeControl : public dtkComposerNode
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
    virtual void setOutputs(void);
    virtual void setVariables(void);
    virtual  int selectBranch(void);
    virtual void begin(void);
    virtual void end(void);

private:
    dtkComposerNodeControlPrivate *d;
};

#endif
