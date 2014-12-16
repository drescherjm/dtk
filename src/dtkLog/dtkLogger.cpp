// Version: $Id$
//
//

// Commentary:
//
//

// Change Log:
//
//

// Code:

#include "dtkLogger.h"
#include "dtkLogger_p.h"
#include "dtkLogDestination.h"
#include "dtkLogModel.h"

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

void dtkLogger::attachModel(dtkLogModel *model)
{
    if(d->models.contains(model))
        return;

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

//
// dtkLogger.cpp ends here
