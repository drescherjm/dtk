/* dtkComposerNodeControlForEach.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Feb 24 16:52:08 2012 (+0100)
 * Version: $Id$
 * Last-Updated: lun. févr. 27 15:37:38 2012 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 10
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODECONTROLFOREACH_H
#define DTKCOMPOSERNODECONTROLFOREACH_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeControl.h"

class dtkComposerNodeControlForEachPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeControlForEach : public dtkComposerNodeControl
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
    dtkComposerNodeControlForEachPrivate *d;
};

#endif
