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

/*! \fn dtkLogger& dtkLogger::instance(void)
 *
 * Returns the logger instance (which is built upon the singleton
 * design pattern).
 */

dtkLogger& dtkLogger::instance(void)
{
    static dtkLogger log;

    return log;
}

/*! \fn dtkLog::Level dtkLogger::level(void) const
 *
 * Returns the logger level.
 */

dtkLog::Level dtkLogger::level(void) const
{
    return d->level;
}

/*! \fn dtkLogger::setLevel(dtkLog::Level level)
 *
 * Sets the logger level using the dtkLog::Level enum.
 */

void dtkLogger::setLevel(dtkLog::Level level)
{
    d->level = level;
}

/*! \fn dtkLog::Level dtkLogger::level(QString level) const
 *
 * Sets the logger level using a string, \e e.g. \c trace, \c debug,
 * \c info, \c warn, \c error or \c fatal.
 */

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

/*! \fn void dtkLogger::attachConsole(void)
 *
 * Attaches the console to the list of logging destinations.
 */

void dtkLogger::attachConsole(void)
{
    d->destinations << d->console;
}

/*! \fn void dtkLogger::attachConsole(dtkLog::Level)
 *
 * Attaches the console to the list of logging destinations for a
 * given level of logging.
 */

void dtkLogger::attachConsole(dtkLog::Level level)
{
    d->destinations << d->console;

    d->levels[d->console] = level;
}

/*! \fn void dtkLogger::detachConsole(void)
 *
 * Detaches the console from the list of logging destinations.
 */

void dtkLogger::detachConsole(void)
{
    d->destinations.removeOne(d->console);
}

/*! \fn void dtkLogger::attachFile(const QString& path)
 *
 * Attaches a file to the list of logging destinations.
 */

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

/*!
 * \class dtkLogger
 * \brief ...
 *
 *
 * \inmodule dtkLog
 */

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
