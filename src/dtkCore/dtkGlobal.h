/* dtkGlobal.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Oct 16 09:54:33 2008 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Mar 17 10:24:15 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 106
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKGLOBAL_H
#define DTKGLOBAL_H

#include <QtCore>
#include <QtGui>
#include <QtDebug>

#include "dtkCoreExport.h"

// /////////////////////////////////////////////////////////////////
// Output colors
// /////////////////////////////////////////////////////////////////

#define DTK_COLOR_FG_BLACK    "\033[00;30m"
#define DTK_COLOR_FG_RED      "\033[00;31m"
#define DTK_COLOR_FG_GREEN    "\033[00;32m"
#define DTK_COLOR_FG_YELLOW   "\033[00;33m"
#define DTK_COLOR_FG_BLUE     "\033[00;34m"
#define DTK_COLOR_FG_MAGENTA  "\033[00;35m"
#define DTK_COLOR_FG_CYAN     "\033[00;36m"
#define DTK_COLOR_FG_WHITE    "\033[00;37m"

#define DTK_COLOR_FG_LTBLACK   "\033[01;30m"
#define DTK_COLOR_FG_LTRED     "\033[01;31m"
#define DTK_COLOR_FG_LTGREEN   "\033[01;32m"
#define DTK_COLOR_FG_LTYELLOW  "\033[01;33m"
#define DTK_COLOR_FG_LTBLUE    "\033[01;34m"
#define DTK_COLOR_FG_LTMAGENTA "\033[01;35m"
#define DTK_COLOR_FG_LTCYAN    "\033[01;36m"
#define DTK_COLOR_FG_LTWHITE   "\033[01;37m"

#define DTK_COLOR_BG_BLACK    "\033[00;40m"
#define DTK_COLOR_BG_RED      "\033[00;41m"
#define DTK_COLOR_BG_GREEN    "\033[00;42m"
#define DTK_COLOR_BG_YELLOW   "\033[00;43m"
#define DTK_COLOR_BG_BLUE     "\033[00;44m"
#define DTK_COLOR_BG_MAGENTA  "\033[00;45m"
#define DTK_COLOR_BG_CYAN     "\033[00;46m"
#define DTK_COLOR_BG_WHITE    "\033[00;47m"

#define DTK_COLOR_FG_BD       "\033[01m"
#define DTK_COLOR_FG_UL       "\033[04m"
#define DTK_NO_COLOR          "\033[00m"

// /////////////////////////////////////////////////////////////////
// Default implementation warning
// /////////////////////////////////////////////////////////////////

#ifdef _MSC_VER
#  define DTK_PRETTY_FUNCTION __FUNCSIG__
#elif defined __GNUG__
#  define DTK_PRETTY_FUNCTION __PRETTY_FUNCTION__
#else 
#  define DTK_PRETTY_FUNCTION __func__
#endif

#define DTK_DEFAULT_IMPLEMENTATION                                      \
    qDebug()                                                            \
    << "Using default implementation of"                                \
    << DTK_PRETTY_FUNCTION                                              \
    << "for"                                                            \
    << this->metaObject()->className()

#define DTK_UNUSED(variable) Q_UNUSED(variable)

#define DTK_DEPRECATED Q_DECL_DEPRECATED

#define DTK_SUCCEED 1
#define DTK_FAILURE 0

// /////////////////////////////////////////////////////////////////
// Helper functions
// /////////////////////////////////////////////////////////////////

inline QString dtkReadFile(const QString& path)
{
    QFile file(path);

    if(!file.open(QFile::ReadOnly))
        qDebug() << "Unable to read file" << path;

    QString contents = file.readAll();

    file.close();

    return contents;
}

inline bool dtkApplicationArgumentsContain(int argc, char **argv, QString value)
{
    for(int i = 1; i < argc; i++)
        if(QString(argv[i]) == value)
            return true;

    return false;
}

inline bool dtkApplicationArgumentsContain(QApplication *application, QString value)
{
    return dtkApplicationArgumentsContain(application->argc(), application->argv(), value); // I know the previous is deprecated but it really shouldn't :-|
}

inline QString dtkApplicationArgumentsValue(int argc, char **argv, QString key)
{
    for(int i = 1; i < argc; i++)
        if(QString(argv[i]) == key)
            return QString(argv[i+1]);

    return QString();
}

inline QString dtkApplicationArgumentsValue(QApplication *application, QString key)
{
    return dtkApplicationArgumentsValue(application->argc(), application->argv(), key); // I know the previous is deprecated but it really shouldn't :-|
}

// /////////////////////////////////////////////////////////////////
// Hash functions
// /////////////////////////////////////////////////////////////////

inline uint qHash(const QStringList &key)
{
    uint hash = 0;
    foreach(QString string, key)
	hash = hash ^ qHash(string);
    return hash;
}

#endif
