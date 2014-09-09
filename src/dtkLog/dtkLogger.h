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

#pragma once

#include <QtCore>
#include <QtDebug>

#include "dtkLogger_p.h"
#include <dtkLogExport.h>

// ///////////////////////////////////////////////////////////////////
// Logging rules
// ///////////////////////////////////////////////////////////////////

void dtkSetLoggingRules(const QByteArray &rules);
void dtkSetLoggingRulesFile(const QString &path);

// ///////////////////////////////////////////////////////////////////
// Example logging rules file
// ///////////////////////////////////////////////////////////////////

// default.*=true
// default.critical=false
// default.warning=true
// default.debug=false

//  *.Category.*=true
// My.Category.B=false

// ///////////////////////////////////////////////////////////////////
// qDebug overload
// ///////////////////////////////////////////////////////////////////

#if defined(qDebug)
#  undef qDebug
#endif

#define qDebug                                                          \
    for (bool enabled = dtkLoggingCategory::defaultCategory().isEnabled(QtDebugMsg); enabled; enabled = false) \
        QMessageLogger(__FILE__, __LINE__, Q_FUNC_INFO, dtkLoggingCategory::defaultCategory().categoryName()).debug

// ///////////////////////////////////////////////////////////////////
// qWarning overload
// ///////////////////////////////////////////////////////////////////

#if defined(qWarning)
#  undef qWarning
#endif

#define qWarning                                                        \
    for (bool enabled = dtkLoggingCategory::defaultCategory().isEnabled(QtWarningMsg); enabled; enabled = false) \
        QMessageLogger(__FILE__, __LINE__, Q_FUNC_INFO, dtkLoggingCategory::defaultCategory().categoryName()).warning

// ///////////////////////////////////////////////////////////////////
// qCritical overload
// ///////////////////////////////////////////////////////////////////

#if defined(qCritical)
#  undef qCritical
#endif

#define qCritical                                                       \
    for (bool enabled = dtkLoggingCategory::defaultCategory().isEnabled(QtCriticalMsg); enabled; enabled = false) \
        QMessageLogger(__FILE__, __LINE__, Q_FUNC_INFO, dtkLoggingCategory::defaultCategory().categoryName()).critical

// ///////////////////////////////////////////////////////////////////
// Helper macro
// ///////////////////////////////////////////////////////////////////

#define DTK_LOG_CATEGORY(categorytype, categoryname)                \
    namespace {                                                     \
        DTKLOG_EXPORT static dtkLoggingCategory categorytype(categoryname);		\
    }

// ///////////////////////////////////////////////////////////////////
// dtkDebug
// ///////////////////////////////////////////////////////////////////

#define dtkDebug                                                        \
    for (bool enabled = dtkLoggingCategory::defaultCategory().isEnabled(QtDebugMsg); enabled; enabled = false)    \
        QMessageLogger(__FILE__, __LINE__, Q_FUNC_INFO, dtkLoggingCategory::defaultCategory().categoryName()).debug

// ///////////////////////////////////////////////////////////////////
// dtkWarning
// ///////////////////////////////////////////////////////////////////

#define dtkWarn                                                         \
    for (bool enabled = dtkLoggingCategory::defaultCategory().isEnabled(QtWarningMsg); enabled; enabled = false)  \
        QMessageLogger(__FILE__, __LINE__, Q_FUNC_INFO, dtkLoggingCategory::defaultCategory().categoryName()).warning

// ///////////////////////////////////////////////////////////////////
// dtkCritical
// ///////////////////////////////////////////////////////////////////

#define dtkCritical                                                     \
    for (bool enabled = dtkLoggingCategory::defaultCategory().isEnabled(QtCriticalMsg); enabled; enabled = false) \
        QMessageLogger(__FILE__, __LINE__, Q_FUNC_INFO, dtkLoggingCategory::defaultCategory().categoryName()).critical

// ///////////////////////////////////////////////////////////////////
// dtkTrace
// ///////////////////////////////////////////////////////////////////

#define dtkTrace                                                        \
    for (bool enabled = dtkLoggingCategory::defaultCategory().isEnabled(QtDebugMsg); enabled; enabled = false) \
        QMessageLogger(__FILE__, __LINE__, Q_FUNC_INFO, dtkLoggingCategory::defaultCategory().categoryName()).debug

// ///////////////////////////////////////////////////////////////////
// dtkInfo
// ///////////////////////////////////////////////////////////////////

#define dtkInfo                                                         \
    for (bool enabled = dtkLoggingCategory::defaultCategory().isEnabled(QtDebugMsg); enabled; enabled = false) \
        QMessageLogger(__FILE__, __LINE__, Q_FUNC_INFO, dtkLoggingCategory::defaultCategory().categoryName()).debug

// ///////////////////////////////////////////////////////////////////
// dtkError
// ///////////////////////////////////////////////////////////////////

#define dtkError                                                        \
    for (bool enabled = dtkLoggingCategory::defaultCategory().isEnabled(QtFatalMsg); enabled; enabled = false) \
        QMessageLogger(__FILE__, __LINE__, Q_FUNC_INFO, dtkLoggingCategory::defaultCategory().categoryName()).critical

/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the logger module of the Qt Toolkit.
**
** GNU Lesser General Public License Usage
**
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
****************************************************************************/

//
// dtkLogger.h ends here
