/* @(#)dtkDistributedWorkerManager.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2013 - Nicolas Niclausse, Inria.
 * Created: 2013/02/14 13:17:10
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
class dtkDistributedPolicy;
class dtkDistributedWork;
class dtkDistributedWorkerManagerPrivate;

class dtkDistributedWorkerManager: public QObject
{
    Q_OBJECT

public:
             dtkDistributedWorkerManager(void);
    virtual ~dtkDistributedWorkerManager(void);

public:
    dtkDistributedWorkerManager(const dtkDistributedWorkerManager& other);
    dtkDistributedWorkerManager& operator = (const dtkDistributedWorkerManager& other);

public:
    void setCommunicator(dtkDistributedCommunicator *comm);
    void       setPolicy(dtkDistributedPolicy *policy);

public:
    void   spawn(dtkDistributedWork *Work);
    void unspawn(void);

public:
    dtkDistributedWorkerManagerPrivate *d;

};





