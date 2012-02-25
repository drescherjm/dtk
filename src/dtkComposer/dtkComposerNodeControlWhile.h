/* dtkComposerNodeControlWhile.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Feb 24 16:52:08 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Sat Feb 25 01:07:27 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 7
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODECONTROLWHILE_H
#define DTKCOMPOSERNODECONTROLWHILE_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeControl.h"

class dtkComposerNodeControlWhilePrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeControlWhile : public dtkComposerNodeControl
{
public:
             dtkComposerNodeControlWhile(void);
    virtual ~dtkComposerNodeControlWhile(void);

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
    QString type(void);

public:
    QString titleHint(void);

private:
    dtkComposerNodeControlWhilePrivate *d;
};

#endif
