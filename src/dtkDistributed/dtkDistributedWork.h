/* @(#)dtkDistributedWork.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2013 - Nicolas Niclausse, Inria.
 * Created: 2013/02/15 13:47:58
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
class dtkDistributedWorker;
class dtkDistributedWorkPrivate;

class dtkDistributedWork : public QObject
{
    Q_OBJECT

public:
             dtkDistributedWork(void);
    virtual ~dtkDistributedWork(void);


public:
    dtkDistributedWork(const dtkDistributedWork& other);
    dtkDistributedWork& operator = (const dtkDistributedWork& other);

public:
    virtual dtkDistributedWork* clone(void);

public:
    virtual void run(void);

public:
    void setWorker(dtkDistributedWorker *worker);

public:
    dtkDistributedWorker *worker(void);

public:
    dtkDistributedWorkPrivate *d;
};


