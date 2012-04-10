/* @(#)dtkComposerEvaluatorSlave.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/04/06 14:23:58
 * Version: $Id$
 * Last-Updated: mar. avril 10 18:20:15 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 20
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSERREMOVESLAVE_H
#define DTKCOMPOSERREMOVESLAVE_H


#include <dtkDistributed/dtkDistributedSlave.h>

class dtkComposerEvaluatorSlavePrivate;

class dtkComposerEvaluatorSlave : public dtkDistributedSlave
{
public:
     dtkComposerEvaluatorSlave(void);
    ~dtkComposerEvaluatorSlave(void);

public:
    void setCount(int count);
    void setServer(QUrl server);
    void setInternalCommunicator(dtkDistributedCommunicator *communicator);

public:
    int exec(void);

private:
    dtkComposerEvaluatorSlavePrivate *d;
};


#endif /* DTKCOMPOSERREMOVESLAVE_H */

