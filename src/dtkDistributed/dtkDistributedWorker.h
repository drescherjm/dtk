/* @(#)dtkDistributedWorker.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2013 - Nicolas Niclausse, Inria.
 * Created: 2013/02/15 13:53:00
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include <QtCore>

#include "dtkDistributed.h"

class dtkDistributedCommunicator;
class dtkDistributedContainerBase;
class dtkDistributedWork;
class dtkDistributedWorkerPrivate;

class dtkDistributedWorker : public QRunnable
{
public:
             dtkDistributedWorker(void);
    virtual ~dtkDistributedWorker(void);


public:
    dtkDistributedWorker(const dtkDistributedWorker& other);
    dtkDistributedWorker& operator = (const dtkDistributedWorker& other);

public:
    void run(void);

public:
    void setMode(const dtkDistributed::Mode& mode);

public:
    void setWid(qlonglong wid);
    void setWct(qlonglong wct);
    void setWork(dtkDistributedWork *work);

public:
    void setCommunicator(dtkDistributedCommunicator *comm);

public:
    qlonglong wid(void);
    qlonglong wct(void);

public:
    void   record(dtkDistributedContainerBase *container);
    void unrecord(dtkDistributedContainerBase *container);

    qlonglong containerId(dtkDistributedContainerBase *container);

public:
    bool master(void);

public:
    dtkDistributedCommunicator *communicator();

private:
    dtkDistributedWorkerPrivate *d;
};
