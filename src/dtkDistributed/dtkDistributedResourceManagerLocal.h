/* @(#)dtkDistributedResourceManagerLocal.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2014 - Nicolas Niclausse, Inria.
 * Created: 2014/04/25 11:38:36
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include "dtkDistributedResourceManager.h"

class dtkDistributedResourceManagerLocalPrivate;

class dtkDistributedResourceManagerLocal : public dtkDistributedResourceManager
{
    Q_OBJECT


public:
    dtkDistributedResourceManagerLocal(void);
    virtual ~dtkDistributedResourceManagerLocal(void);

public slots:
    QByteArray status(void);
    QString submit(QString input);
    QString deljob(QString jobid);

private:
    dtkDistributedResourceManagerLocalPrivate *d;
};



