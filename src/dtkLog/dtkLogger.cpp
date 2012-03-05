/* dtkLogger.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Thu Mar  1 17:19:52 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Mar  5 11:13:23 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 87
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

void dtkLogger::attachConsole(void)
{
    d->destinations << d->console;
}

void dtkLogger::detachConsole(void)
{
    d->destinations.removeOne(d->console);
}

void dtkLogger::attachFile(const QString& path)
{
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

void dtkLogger::attachModel(dtkLogModel *model)
{
    d->models[model] = dtkLogDestinationPointer(new dtkLogDestinationModel(model));

    d->destinations << d->models[model];
}

void dtkLogger::detachModel(dtkLogModel *model)
{
    if(!d->models.contains(model))
        return;

    d->destinations.removeOne(d->models[model]);

    d->models.remove(model);
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
