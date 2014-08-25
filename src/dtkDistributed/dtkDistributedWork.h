// Version: $Id$
//
//

// Commentary:
//
//

// Change Log:
//
//

// Code:

#pragma once

#include <dtkDistributedExport>

#include <QtCore>

class dtkDistributedCommunicator;
class dtkDistributedWorker;
class dtkDistributedWorkPrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedWork : public QObject
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
    void barrier(void);

public:
    qlonglong wid(void);
    qlonglong wct(void);

public:
    void setWorker(dtkDistributedWorker *worker);

public:
    dtkDistributedWorker *worker(void);

public:
    dtkDistributedWorkPrivate *d;
};



//
// dtkDistributedWork.h ends here
