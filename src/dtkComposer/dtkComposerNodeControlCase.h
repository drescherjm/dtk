/* dtkComposerNodeControlCase.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: mar. mai 15 17:01:00 2012 (+0200)
 * Version: $Id$
 * Last-Updated: lun. mai 21 11:00:14 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 11
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERNODECONTROLCASE_H
#define DTKCOMPOSERNODECONTROLCASE_H


#include "dtkComposerNodeControl.h"

class dtkComposerNodeControlCasePrivate;

class  dtkComposerNodeControlCase : public dtkComposerNodeControl
{
public:
             dtkComposerNodeControlCase(void);
    virtual ~dtkComposerNodeControlCase(void);

public:
    int blockCount(void);
    dtkComposerNodeLeaf *header(void);
    dtkComposerNodeLeaf *footer(void);
    dtkComposerNodeComposite *block(int id);

public:
    void setInputs(void);
    void setConditions(void);
    void setOutputs(void);
    void setVariables(void);
     int selectBranch(void);
    void begin(void);
    void end(void);

public:
    void addBlock(void);
    void addBlock(dtkComposerNodeComposite *c);
    void removeBlock(int id);

public:
    QString type(void);

public:
    QString titleHint(void);

private:
    dtkComposerNodeControlCasePrivate *d;
};

#endif
