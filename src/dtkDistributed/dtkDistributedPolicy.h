//
// Copyright (C) 2013 - Nicolas Niclausse, Inria.
//

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
    Q_INVOKABLE QStringList types(void) const;

public:
    void addHost(const QString& host);
    void setType(const QString& type);
    void setNWorkers(qlonglong nworkers);
    void setHostsFromEnvironment(void);

public:
    QStringList    hosts(void) const;

public:
    dtkDistributedCommunicator *communicator(void) const;

public:
    dtkDistributedPolicyPrivate *d;
};

//
// dtkDistributedPolicy.h ends here
