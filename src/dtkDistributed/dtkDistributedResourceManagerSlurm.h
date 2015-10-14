/* dtkDistributedResourceManagerSlurm.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2015 - Nicolas Niclausse, Inria.
 * Created: 2015/10/12 13:25:04
 */

#pragma once

#include "dtkDistributedResourceManager.h"

class dtkDistributedResourceManagerSlurm : public dtkDistributedResourceManager
{
    Q_OBJECT

public slots:
    QByteArray status(void);
    QString submit(QString input);
    QString deljob(QString jobid);
};

