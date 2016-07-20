/* dtkComposerNodeControlDoWhile.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Feb 24 16:52:08 2012 (+0100)
 * Version: $Id$
 * Last-Updated: mer. mars 28 13:58:50 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 9
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERNODECONTROLDOWHILE_H
#define DTKCOMPOSERNODECONTROLDOWHILE_H

#include "dtkComposerSupportExport.h"
#include "dtkComposerNodeControl.h"

class dtkComposerNodeControlDoWhilePrivate;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerNodeControlDoWhile : public dtkComposerNodeControl
{
public:
    dtkComposerNodeControlDoWhile(void);
    virtual ~dtkComposerNodeControlDoWhile(void);

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
    dtkComposerNodeControlDoWhilePrivate *d;
};

#endif
