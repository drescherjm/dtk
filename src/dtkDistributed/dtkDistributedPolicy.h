/* @(#)dtkDistributedPolicy.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2013 - Nicolas Niclausse, Inria.
 * Created: 2013/02/18 15:10:52
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include <QtCore>

class dtkDistributedPolicyPrivate;
class dtkDistributedCommunicator;

class dtkDistributedPolicy : public QObject
{
    Q_OBJECT

public:
             dtkDistributedPolicy(void);
    virtual ~dtkDistributedPolicy(void);

public:
    dtkDistributedPolicy(const dtkDistributedPolicy& other);
    dtkDistributedPolicy& operator = (const dtkDistributedPolicy& other);

public:
    enum Type {
        MP,
        MT,
        HYB
    };

public:
    void addHost(QString host);
    void setType(dtkDistributedPolicy::Type);
    void setType(const QString& type);
    void setNThreads(qlonglong nthreads);

public:
    QStringList    hosts(void);
    qlonglong   nthreads(void);

public:
    dtkDistributedCommunicator *communicator(void);

public:
    dtkDistributedPolicyPrivate *d;
};



