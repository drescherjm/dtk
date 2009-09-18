/* dtkLog.h --- 
 * 
 * Author: Jean-Christophe Lombardo
 * Copyright (C) 2008-2009 - Jean-Christophe Lombardo, Inria.
 * Created: Thu May 14 14:02:22 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Fri Sep 18 23:04:40 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 84
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKLOG_H
#define DTKLOG_H

#include <QtCore>

#include "dtkCoreExport.h"

// /////////////////////////////////////////////////////////////////
// dtkLog
// /////////////////////////////////////////////////////////////////

class DTKCORE_EXPORT dtkLog
{
public:
    enum Level { Output, Error, Debug, Warning, Critical, Fatal };

    typedef void (*Handler)(Level level, const QString &message);

    dtkLog& operator<<(int value);
    dtkLog& operator<<(float value);
    dtkLog& operator<<(double value);
    dtkLog& operator<<(QString value);

    ~dtkLog(void);

    static dtkLog   output(QString source = "default");
    static dtkLog    error(QString source = "default");
    static dtkLog    debug(QString source = "default");
    static dtkLog  warning(QString source = "default");
    static dtkLog critical(QString source = "default");
    static dtkLog    fatal(QString source = "default");

    static void   registerHandler(Handler handler, QString source = "default");
    static void unregisterHandler(Handler handler, QString source = "default");

    static void disableRedirection(void);

private:
     dtkLog(QString source, Level level);

private:
    Level   m_level;
    QString m_source;
    QString m_log;

private:
    static QMultiMap<QString, Handler> s_handlers;
};

// /////////////////////////////////////////////////////////////////
// dtkLogEvent
// /////////////////////////////////////////////////////////////////

class DTKCORE_EXPORT dtkLogEvent : public QEvent
{
public:
    dtkLogEvent(dtkLog::Level level, const QString & msg);
    
    dtkLog::Level level(void) const;

    QString message(void) const;

private:
    dtkLog::Level m_level;

    QString m_message;

private:
    static Type s_type;
};

// /////////////////////////////////////////////////////////////////
// Helper functions
// /////////////////////////////////////////////////////////////////

DTKCORE_EXPORT dtkLog dtkOutput(void);
DTKCORE_EXPORT dtkLog dtkError(void);
DTKCORE_EXPORT dtkLog dtkDebug(void);
DTKCORE_EXPORT dtkLog dtkWarning(void);
DTKCORE_EXPORT dtkLog dtkCritical(void);
DTKCORE_EXPORT dtkLog dtkFatal(void);

#endif
