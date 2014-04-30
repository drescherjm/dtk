/* @(#)dtkDistributedResourceManager.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2014 - Nicolas Niclausse, Inria.
 * Created: 2014/04/25 07:08:51
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include <QObject>


class dtkDistributedResourceManager : public QObject
{
    Q_OBJECT

public:
             dtkDistributedResourceManager(void);
    virtual ~dtkDistributedResourceManager(void);

    static QString protocol(void) { return "1.0"; };

public slots:
    virtual QByteArray status(void) = 0;
    virtual QString submit(QString input) = 0;
    virtual QString deljob(QString jobid) = 0;

};
