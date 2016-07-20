/* dtkDistributedJob.cpp ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2011 - Nicolas Niclausse, Inria.
 * Created: Tue Feb 16 16:26:17 2010 (+0100)
 * Version: $Id$
 * Last-Updated: jeu. avril 12 11:05:16 2012 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 126
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkDistributedJob.h"

class dtkDistributedJobPrivate
{
public:
    QString  id;
    QString  username;
    QString  name;
    QString  queue;
    QDateTime qtime; // queue time
    QDateTime stime; // start time
    dtkDistributedJob::State  state;
    QString walltime;
    QString script;
    QString resources;
};

dtkDistributedJob::dtkDistributedJob(void) : QObject(), d(new dtkDistributedJobPrivate)
{
}

dtkDistributedJob::~dtkDistributedJob(void)
{
    delete d;

    d = NULL;
}

QString dtkDistributedJob::Id(void)
{
    return d->id;
}

void dtkDistributedJob::setId(const QString& id)
{
    d->id = id;
}

QString dtkDistributedJob::Name(void)
{
    return d->name;
}

void dtkDistributedJob::setName(const QString& name)
{
    d->name = name;
}

QString dtkDistributedJob::Queue(void)
{
    return d->queue;
}

void dtkDistributedJob::setQueue(const QString& queue)
{
    d->queue = queue;
}

dtkDistributedJob::State dtkDistributedJob::state(void)
{
    return d->state;
}

void dtkDistributedJob::setState(const QString& state)
{
    if (state == "Running")    d->state = dtkDistributedJob::Running;

    if (state == "Blocked")    d->state = dtkDistributedJob::Blocked;

    if (state == "Queued")     d->state = dtkDistributedJob::Queued;

    if (state == "Suspended")  d->state = dtkDistributedJob::Suspended;

    if (state == "Scheduled")  d->state = dtkDistributedJob::Scheduled;

    if (state == "EndedOK")    d->state = dtkDistributedJob::EndedOK;

    if (state == "EndedError") d->state = dtkDistributedJob::EndedError;
}

QString dtkDistributedJob::Username(void)
{
    return d->username;
}

void dtkDistributedJob::setUsername(const QString& username)
{
    d->username = username;
}

QString dtkDistributedJob::Script(void)
{
    return d->script;
}

void dtkDistributedJob::setScript(const QString& script)
{
    d->script = script;
}

QString dtkDistributedJob::Resources(void)
{
    return d->resources;
}

void dtkDistributedJob::setResources(const QString& resources)
{
    d->resources = resources;
}

QDateTime dtkDistributedJob::Stime(void)
{
    return d->stime;
}

#include <time.h>

void dtkDistributedJob::setStime(qint64 stime)
{
    if (stime == 0)
        return;

#if QT_VERSION > 0x0406FF
    d->stime = QDateTime::fromMSecsSinceEpoch(stime);
#else
    QDateTime dtime = QDateTime(QDate(1970, 1, 1));
    dtime.addMSecs(stime);

    d->stime = dtime;
#endif
}

QDateTime dtkDistributedJob::Qtime(void)
{
    return d->qtime;
}

void dtkDistributedJob::setQtime(qint64 qtime)
{
    if (qtime == 0)
        return;

#if QT_VERSION > 0x0406FF
    d->qtime = QDateTime::fromMSecsSinceEpoch(qtime);
#else
    QDateTime dtime = QDateTime(QDate(1970, 1, 1));
    dtime.addMSecs(qtime);

    d->qtime = dtime;
#endif
}

QString dtkDistributedJob::Walltime(void)
{
    return d->walltime;
}

void dtkDistributedJob::setWalltime(const QString& walltime)
{
    d->walltime = walltime;
}
