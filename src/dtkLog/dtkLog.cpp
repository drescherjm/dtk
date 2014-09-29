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

#include "dtkLog.h"
#include "dtkLogExport.h"

#include <QtCore>

/*!
 * \namespace dtkLog
 *
 * \brief Contains main enumeration used throughout the Log module.
 *
 * \inmodule dtkLog
 */

/*!
 * \enum dtkLog::Level
 *
 * This enum type specifies a corner in a rectangle:
 *
 * \value Trace
 *        ...
 * \value Debug
 *        ...
 * \value Info
 *        ...
 * \value Warn
 *        ...
 * \value Error
 *        ...
 * \value Fatal
 *        ...
 */

/*!
 * \macro dtkTrace()
 * \relates dtkLog
 *
 * Provides a stream to send Trace level messages.
 *
 * The output will be carried on depending on the dtkLogger instance log Level.
 */

/*!
 * \macro dtkDebug()
 * \relates dtkLog
 *
 * Provides a stream to send Debug level messages.
 *
 * The output will be carried on depending on the dtkLogger instance log Level.
 */

/*!
 * \macro dtkInfo()
 * \relates dtkLog
 *
 * Provides a stream to send Info level messages.
 *
 * The output will be carried on depending on the dtkLogger instance log Level.
 */

/*!
 * \macro dtkWarn()
 * \relates dtkLog
 *
 * Provides a stream to send Warn level messages.
 *
 * The output will be carried on depending on the dtkLogger instance log Level.
 */

/*!
 * \macro dtkError()
 * \relates dtkLog
 *
 * Provides a stream to send Error level messages.
 *
 * The output will be carried on depending on the dtkLogger instance log Level.
 */

/*!
 * \macro dtkFatal()
 * \relates dtkLog
 *
 * Provides a stream to send Fatal level messages.
 *
 * The output will be carried on depending on the dtkLogger instance log Level.
 */

/*!
 * \fn QString DTKLOG_EXPORT dtkLogPath(QCoreApplication *application)
 * \relates dtkLog
 *
 * Convenience method to return the path to an application's log file
 * using the standard data location path.
 */

QString DTKLOG_EXPORT dtkLogPath(QCoreApplication *application)
{
    return QDir(QStandardPaths::standardLocations(QStandardPaths::DataLocation).first()).filePath(QString("%1.log").arg(application->applicationName()));
}

//
// dtkLog.cpp ends here
