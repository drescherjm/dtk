/* dtkComposerNodeControlWhile.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Feb 24 16:52:08 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Apr  4 09:57:04 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 10
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#pragma once

#include "dtkComposerNodeControl.h"

class dtkComposerNodeControlWhilePrivate;

class  dtkComposerNodeControlWhile : public dtkComposerNodeControl
{
public:
     dtkComposerNodeControlWhile(void);
    ~dtkComposerNodeControlWhile(void);

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
