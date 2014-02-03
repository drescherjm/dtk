/* dtkComposerNodeControlFor.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Feb 15 09:12:58 2012 (+0100)
 * Version: $Id$
 * Last-Updated: mer. mars 28 13:59:31 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 18
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODECONTROLFOR_H
#define DTKCOMPOSERNODECONTROLFOR_H

#include "dtkComposerExport.h"
#include "dtkComposerNodeControl.h"

class dtkComposerNodeControlForPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeControlFor : public dtkComposerNodeControl
{
public:
             dtkComposerNodeControlFor(void);
    virtual ~dtkComposerNodeControlFor(void);

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
    dtkComposerNodeControlForPrivate *d;
};

#endif
