/* dtkComposerNodeControlForEach.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Feb 24 16:52:08 2012 (+0100)
 * Version: $Id$
 * Last-Updated: ven. sept. 20 09:08:54 2013 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 14
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODECONTROLFOREACH_H
#define DTKCOMPOSERNODECONTROLFOREACH_H

#include "dtkComposerSupportExport.h"
#include "dtkComposerNodeControl.h"

class dtkComposerNodeControlForEachPrivate;

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeControlForEach interface
// /////////////////////////////////////////////////////////////////

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeControlForEach : public dtkComposerNodeControl
{
public:
             dtkComposerNodeControlForEach(void);
    virtual ~dtkComposerNodeControlForEach(void);

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

public:
    QString type(void);

public:
    QString titleHint(void);

private:
    dtkComposerNodeControlForEachPrivate *d;
};

#endif
