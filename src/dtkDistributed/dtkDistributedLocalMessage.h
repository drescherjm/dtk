/* @(#)dtkDistributedLocalMessage.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2013 - Nicolas Niclausse, Inria.
 * Created: 2013/02/21 15:41:35
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#pragma once

#include <QtCore>

class dtkDistributedLocalMessagePrivate;

class dtkDistributedLocalMessage
{
public:
    dtkDistributedLocalMessage(void);
    dtkDistributedLocalMessage(QVariant &v, qint32 source, qint32 tag);
    virtual ~dtkDistributedLocalMessage(void);

public:
    void        lock(void);
    void      unlock(void);
    qint32       tag(void);
    void        wait(void);
    qint32    source(void);
    void        wake(void);
    bool wait_for_data(void);
    QVariant& data(void);

public:
    void setWaitData(bool wait_value);
    void     setData(QVariant data);
    void      setTag(qint32 tag);
    void   setSource(qint32 source);

private:
    dtkDistributedLocalMessagePrivate *d;
};




