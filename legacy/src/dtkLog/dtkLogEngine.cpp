/* dtkLogEngine.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Mar  1 16:18:42 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Mar 18 12:39:12 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 82
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkConfig.h>

#include "dtkLog.h"
#include "dtkLogger.h"
#include "dtkLogger_p.h"
#include "dtkLogEngine.h"

#if defined(DTK_HAVE_MPI)
#include <mpi.h>
#endif

// /////////////////////////////////////////////////////////////////
// Helper functions
// /////////////////////////////////////////////////////////////////

QString dtkLogLevel2String(dtkLog::Level level)
{
    switch(level) {
    case dtkLog::Trace: return "TRACE"; break;
    case dtkLog::Debug: return "DEBUG"; break;
    case dtkLog::Info:  return "INFO "; break;
    case dtkLog::Warn:  return "WARN "; break;
    case dtkLog::Error: return "ERROR"; break;
    case dtkLog::Fatal: return "FATAL"; break;
    default:
        return "UNKNOWN";
        break;
    };
}

// /////////////////////////////////////////////////////////////////
// dtkLogEnginePrivate
// /////////////////////////////////////////////////////////////////

class dtkLogEnginePrivate
{
public:
    dtkLogEnginePrivate(void) : stream(&buffer) {}

public:
    void write(void);

public:
    dtkLog::Level level;

public:
    QDebug stream;

public:
    QString buffer;

public:
    bool custom;
};

void dtkLogEnginePrivate::write(void)
{

    QString rank ;

#if defined(DTK_HAVE_MPI)

    if (MPI::Is_initialized())
        rank = "rank " + QString::number(MPI::COMM_WORLD.Get_rank());

#endif

    if (!rank.isEmpty()) {
        const QString message = QString("%1 - %2 - %3 - %4")
            .arg(qPrintable(dtkLogLevel2String(this->level)))
            .arg(QDateTime::currentDateTime().toString())
            .arg(rank)
            .arg(this->buffer);

        QMutexLocker lock(&(dtkLogger::instance().d->mutex));

	if(!this->custom)
	    dtkLogger::instance().write(message);
	else
	    dtkLogger::instance().write(message, level);

    } else {

        const QString message = QString("%1 - %2 - %3")
            .arg(qPrintable(dtkLogLevel2String(this->level)))
            .arg(QDateTime::currentDateTime().toString())
            .arg(this->buffer);

        QMutexLocker lock(&(dtkLogger::instance().d->mutex));

	if(!this->custom)
	    dtkLogger::instance().write(message);
	else
	    dtkLogger::instance().write(message, level);

    }
}

// /////////////////////////////////////////////////////////////////
// dtkLogEngine
// /////////////////////////////////////////////////////////////////

dtkLogEngine::dtkLogEngine(dtkLog::Level level, bool custom) : d(new dtkLogEnginePrivate)
{
    d->level = level;
    d->custom = custom;
}

dtkLogEngine::~dtkLogEngine(void)
{
    d->write();

    delete d;

    d = NULL;
}

QDebug dtkLogEngine::stream(void)
{
    return d->stream;
}
