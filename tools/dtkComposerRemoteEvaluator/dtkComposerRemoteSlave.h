/* @(#)dtkComposerRemoteSlave.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2012 - Nicolas Niclausse, Inria.
 * Created: 2012/04/06 14:23:58
 * Version: $Id$
 * Last-Updated: ven. avril  6 16:50:13 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 19
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

class dtkComposerRemoteSlavePrivate;

class dtkComposerRemoteSlave : public dtkDistributedSlave
{
public:
     dtkComposerRemoteSlave(void);
    ~dtkComposerRemoteSlave(void);

public:
    void setCount(int count);
    void setServer(QUrl server);
    void setInternalCommunicator(dtkDistributedCommunicator *communicator);

public:
    int exec(void);

private:
    dtkComposerRemoteSlavePrivate *d;
};


#endif /* DTKCOMPOSERREMOVESLAVE_H */

