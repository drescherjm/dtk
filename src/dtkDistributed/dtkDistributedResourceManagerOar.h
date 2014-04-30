/* @(#)dtkDistributedResourceManagerOar.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2014 - Nicolas Niclausse, Inria.
 * Created: 2014/04/25 08:16:42
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include "dtkDistributedResourceManager.h"

class dtkDistributedResourceManagerOarPrivate;

class dtkDistributedResourceManagerOar : public dtkDistributedResourceManager
{
    Q_OBJECT

public slots:
    QByteArray status(void);
    QString submit(QString input);
    QString deljob(QString input);
};
