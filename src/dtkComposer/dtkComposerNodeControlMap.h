/* dtkComposerNodeControlMap.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: lun. juin 18 16:08:06 2012 (+0100)
 * Version: $Id$
 * Last-Updated: lun. juin 18 16:08:29 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 14
 */

/* Commentary:
 *
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODECONTROLMAP_H
#define DTKCOMPOSERNODECONTROLMAP_H


#include "dtkComposerNodeControl.h"

class dtkComposerNodeControlMapPrivate;

class  dtkComposerNodeControlMap : public dtkComposerNodeControl
{
public:
             dtkComposerNodeControlMap(void);
    virtual ~dtkComposerNodeControlMap(void);

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
    dtkComposerNodeControlMapPrivate *d;
};

#endif
