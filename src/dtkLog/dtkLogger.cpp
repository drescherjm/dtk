/* dtkLogger.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Mar  1 17:19:52 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Mar 18 12:57:12 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 128
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkLogger.h"
#include "dtkLogger_p.h"
#include "dtkLogDestination.h"

dtkLogger& dtkLogger::instance(void)
{
    static dtkLogger log;

    return log;
}

dtkLog::Level dtkLogger::level(void) const
{
    return d->level;
}

void dtkLogger::setLevel(dtkLog::Level level)
{
    d->level = level;
}

void dtkLogger::setLevel(QString level)
{

    if (level == "trace")
        d->level = dtkLog::Trace;
    else if (level == "debug")
        d->level = dtkLog::Debug;
    else if (level == "info")
        d->level = dtkLog::Info;
    else if (level == "warn")
        d->level = dtkLog::Warn;
    else if (level == "error")
        d->level = dtkLog::Error;
    else if (level == "fatal")
        d->level = dtkLog::Fatal;
}

void dtkLogger::attachConsole(void)
{
    d->destinations << d->console;
}

void dtkLogger::attachConsole(dtkLog::Level level)
{
    d->destinations << d->console;

    d->levels[d->console] = level;
}

void dtkLogger::detachConsole(void)
{
    d->destinations.removeOne(d->console);
}

void dtkLogger::attachFile(const QString& path)
{
    if(d->files.contains(path))
        return;

    d->files[path] = dtkLogDestinationPointer(new dtkLogDestinationFile(path));

    d->destinations << d->files[path];
}

void dtkLogger::detachFile(const QString& path)
{
    if(!d->files.contains(path))
        return;

    d->destinations.removeOne(d->files[path]);

    d->files.remove(path);
}

dtkLogger::dtkLogger(void) : d(new dtkLoggerPrivate)
{
    d->level = dtkLog::Info;

    d->console = dtkLogDestinationPointer(new dtkLogDestinationConsole);
}

dtkLogger::~dtkLogger(void)
{
    delete d;

    d = NULL;
}

void dtkLogger::write(const QString& message)
{
    for(int i = 0; i < d->destinations.count(); i++)
        d->destinations.at(i)->write(message);
}

void dtkLogger::write(const QString& message, dtkLog::Level level)
{
    for(int i = 0; i < d->destinations.count(); i++) {

        if(d->levels.keys().contains(d->destinations.at(i))) {
            if(level > d->levels[d->destinations.at(i)]) {
                d->destinations.at(i)->write(message);
            }
        } else {
            d->destinations.at(i)->write(message);
        }
    }
}
