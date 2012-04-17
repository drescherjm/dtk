/* dtkLogger.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Mar  1 17:18:31 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Apr  4 10:03:36 2012 (+0200)
 *           By: tkloczko
 *     Update #: 32
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
#include <QtGui>

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

public:
    void attachConsole(void);
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

private:
    dtkLogger& operator=(const dtkLogger& other);

private:
    dtkLoggerPrivate *d;

private:
    friend class dtkLogEngine;
    friend class dtkLogEnginePrivate;
};

#endif
