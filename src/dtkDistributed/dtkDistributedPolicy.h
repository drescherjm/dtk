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

class dtkDistributedPolicyPrivate;
class dtkDistributedCommunicator;

class DTKDISTRIBUTED_EXPORT dtkDistributedPolicy : public QObject
{
    Q_OBJECT

public:
             dtkDistributedPolicy(void);
    virtual ~dtkDistributedPolicy(void);

public:
    dtkDistributedPolicy(const dtkDistributedPolicy& other);
    dtkDistributedPolicy& operator = (const dtkDistributedPolicy& other);

public:
    Q_INVOKABLE QStringList types(void);

public:
    void addHost(QString host);
    void setType(const QString& type);
    void setNWorkers(qlonglong nworkers);

public:
    QStringList    hosts(void);

public:
    dtkDistributedCommunicator *communicator(void);

public:
    dtkDistributedPolicyPrivate *d;
};

//
// dtkDistributedPolicy.h ends here
