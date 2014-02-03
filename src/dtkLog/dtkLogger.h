/* dtkLogger.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Mar  1 17:18:31 2012 (+0100)
 * Version: $Id$
 * Last-Updated: lun. févr.  3 13:07:49 2014 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 41
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKLOGGER_H
#define DTKLOGGER_H

#include "dtkLog.h"
#include "dtkLogExport.h"

#include <QtCore>
#include <QtWidgets>

class dtkLoggerPrivate;
class dtkLogDestination;
class dtkLogModel;

class DTKLOG_EXPORT dtkLogger
{
public:
    static dtkLogger& instance(void);

public:
    dtkLog::Level level(void) const;

public:
    void setLevel(dtkLog::Level level);
    void setLevel(QString level);

public:
    void attachConsole(void);
    void attachConsole(dtkLog::Level level);
    void detachConsole(void);

public:
    void attachFile(const QString& path);
    void detachFile(const QString& path);

public:
    void attachText(QPlainTextEdit *editor);
    void detachText(QPlainTextEdit *editor);

public:
    void attachModel(dtkLogModel *model);
    void detachModel(dtkLogModel *model);

private:
     dtkLogger(void);
     dtkLogger(const dtkLogger& other);
    ~dtkLogger(void);

private:
    void write(const QString& message);
    void write(const QString& message, dtkLog::Level level);

private:
    dtkLogger& operator=(const dtkLogger& other);

private:
    dtkLoggerPrivate *d;

private:
    friend class dtkLogEngine;
    friend class dtkLogEnginePrivate;
};

#endif
