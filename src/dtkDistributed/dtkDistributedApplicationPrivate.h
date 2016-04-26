/* @(#)dtkDistributedApplicationPrivate.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2016 - Nicolas Niclausse, Inria.
 * Created: 2016/04/25 13:13:00
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include "dtkDistributedExport.h"

#include <dtkCore/dtkApplicationPrivate.h>
#include <dtkDistributedPolicy.h>


class DTKDISTRIBUTED_EXPORT dtkDistributedApplicationPrivate: public dtkApplicationPrivate
{
public:
             dtkDistributedApplicationPrivate(void);
    virtual ~dtkDistributedApplicationPrivate(void);

public:
    void initialize(void);
    void exec(QRunnable *task);
    void spawn(QMap<QString, QString> options = QMap<QString, QString>() );
    void unspawn(void);

public:
    dtkDistributedPolicy policy;
    bool spawned;
    bool nospawn;
    QString wrapper;
    QString smp;

};



