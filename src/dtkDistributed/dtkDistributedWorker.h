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

class dtkDistributedCommunicator;
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
    void setWid(qlonglong wid);
    void setWct(qlonglong wct);
    void setWork(dtkDistributedWork *work);

public:
    void setCommunicator(dtkDistributedCommunicator *comm);

public:
    qlonglong wid(void);
    qlonglong wct(void);

public:
    qlonglong containerId(void);

public:
    bool master(void);

public:
    dtkDistributedCommunicator *communicator();

private:
    dtkDistributedWorkerPrivate *d;
};
