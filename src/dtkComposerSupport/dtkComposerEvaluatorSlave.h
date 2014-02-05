/* dtkComposerEvaluatorSlave.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/04/06 14:23:58
 * Version: $Id$
 * Last-Updated: mer. févr.  5 10:21:27 2014 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 36
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPOSEREVALUATORSLAVE_H
#define DTKCOMPOSEREVALUATORSLAVE_H

#include "dtkComposerSupportExport.h"

#include <dtkDistributedSupport/dtkDistributedSlave.h>

class dtkComposerFactory;
class dtkComposerEvaluatorSlavePrivate;

class DTKCOMPOSERSUPPORT_EXPORT dtkComposerEvaluatorSlave : public dtkDistributedSlave
{

public:
     dtkComposerEvaluatorSlave(void);
    ~dtkComposerEvaluatorSlave(void);

public:
    void setCount(int count);
    void setServer(QUrl server);
    void setFactory(dtkComposerFactory *factory);
    void setInternalCommunicator(dtkDistributedCommunicator *communicator);

public:
    int exec(void);

private:
    dtkComposerEvaluatorSlavePrivate *d;
};


#endif /* DTKCOMPOSEREVALUATORLAVE_H */

