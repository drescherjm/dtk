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

#include <QtCore>

#include "dtkDistributed.h"
#include "dtkDistributedExport.h"

class dtkDistributedCommunicator;
class dtkDistributedContainer;
class dtkDistributedWork;
class dtkDistributedWorkerPrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedWorker : public QRunnable
{
public:
             dtkDistributedWorker(void);
    virtual ~dtkDistributedWorker(void);


public:
    dtkDistributedWorker(const dtkDistributedWorker& other);
    dtkDistributedWorker& operator = (const dtkDistributedWorker& other);

public:
    void run(void);

/* public: */
/*     void setMode(const dtkDistributed::Mode& mode); */

public:
    void setWid(qlonglong wid);
    void setWct(qlonglong wct);
    void setWork(dtkDistributedWork *work);

public:
    void setCommunicator(dtkDistributedCommunicator *comm);

public:
    qlonglong wid(void);
    qlonglong wct(void);

/* public: */
/*     qlonglong record(dtkDistributedContainer *container); */

/*     void unrecord(dtkDistributedContainer *container); */

/*     qlonglong containerId(const dtkDistributedContainer *container); */

public:
    bool master(void);

public:
    dtkDistributedCommunicator *communicator();

private:
    dtkDistributedWorkerPrivate *d;
};

//
// dtkDistributedWorker.h ends here
