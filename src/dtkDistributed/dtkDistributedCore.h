/* dtkDistributedCore.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Feb 16 16:24:27 2010 (+0100)
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include <QObject>

class dtkDistributedCpu;
class dtkDistributedJob;
class dtkDistributedCorePrivate;

class  dtkDistributedCore : public QObject
{
    Q_OBJECT

public:
     dtkDistributedCore(dtkDistributedCpu *parent, qint64 id);
    ~dtkDistributedCore(void);

public:
    dtkDistributedJob *job(void);

public:
    void setJob(dtkDistributedJob *job);
    void delJob(void);

private:
    dtkDistributedCorePrivate *d;
};

