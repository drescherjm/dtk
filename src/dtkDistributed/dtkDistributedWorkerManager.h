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

#include "dtkDistributedExport.h"

#include <QtCore>

class dtkDistributedCommunicator;
class dtkDistributedPolicy;
class dtkDistributedWork;
class dtkDistributedWorkerManagerPrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedWorkerManager: public QObject
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
    void   spawn(void);
    void    exec(dtkDistributedWork *work);
    void unspawn(void);

public:
    dtkDistributedWorkerManagerPrivate *d;

};

//
// dtkDistributedWorkerManager.h ends here
