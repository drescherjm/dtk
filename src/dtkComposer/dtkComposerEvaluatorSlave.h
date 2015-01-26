/* dtkComposerEvaluatorSlave.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/04/06 14:23:58
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include "dtkComposerExport.h"

#include <dtkDistributed/dtkDistributedSlave.h>

class dtkComposerNodeFactory;
class dtkDistributedCommunicator;
class dtkComposerEvaluatorSlavePrivate;

class DTKCOMPOSER_EXPORT dtkComposerEvaluatorSlave : public dtkDistributedSlave
{

public:
     dtkComposerEvaluatorSlave(void);
    ~dtkComposerEvaluatorSlave(void);

public:
    void setCount(int count);
    void setServer(QUrl server);
    void setFactory(dtkComposerNodeFactory *factory);
    void setInternalCommunicator(dtkDistributedCommunicator *communicator);

public:
    int exec(void);

private:
    dtkComposerEvaluatorSlavePrivate *d;
};

