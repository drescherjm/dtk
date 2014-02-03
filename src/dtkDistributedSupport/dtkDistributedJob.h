/* dtkDistributedJob.h --- 
 * 
 * Author: Nicolas Niclausse
 * Copyright (C) 2011 - Nicolas Niclausse, Inria.
 * Created: Tue Feb 16 16:24:27 2010 (+0100)
 * Version: $Id$
 * Last-Updated: mer. août 10 12:54:44 2011 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 75
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKDISTRIBUTEDJOB_H
#define DTKDISTRIBUTEDJOB_H

#include <QObject>
#include <QDateTime>

#include "dtkDistributedExport.h"

class dtkDistributedJobPrivate;

class DTKDISTRIBUTED_EXPORT dtkDistributedJob : public QObject
{
    Q_OBJECT

public:
     dtkDistributedJob(void);
    ~dtkDistributedJob(void);

    enum State {
        Running    = 0x1,
        Queued     = 0x2,
        Suspended  = 0x4,
        Blocked    = 0x8,
        Ending     = 0x16,
        Scheduled  = 0x32,
        EndedOK    = 0x64,
        EndedError = 0x128
    };

    State state(void);
    QString Id(void);
    QString Queue(void);
    QString Username(void);
    QString Name(void);
    QDateTime Stime(void);
    QDateTime Qtime(void);
    QString Walltime(void);
    QString Script(void);
    QString Resources(void);

    void setState(const QString& state);
    void setQueue(const QString& queue);
    void setId(const QString& id);
    void setUsername(const QString& username);
    void setName(const QString& name);
    void setStime(qint64 stime);
    void setQtime(qint64 qtime);
    void setWalltime(const QString& walltime);
    void setResources(const QString& resources);
    void setScript(const QString& script);

private:
    dtkDistributedJobPrivate *d;
};

#endif
