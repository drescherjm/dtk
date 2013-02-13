/* dtkLogger.h --- 
 * 
 * Author: Julien Wintz
 * Created: Wed Feb 13 12:18:35 2013 (+0100)
 * Version: 
 * Last-Updated: Wed Feb 13 15:32:41 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 22
 */

/* Change Log:
 * 
 */

#pragma once

#include <QtCore>
#include <QtDebug>

// ///////////////////////////////////////////////////////////////////
// Logging rules
// ///////////////////////////////////////////////////////////////////

void dtkSetLoggingRules(const QByteArray &rules);
void dtkSetLoggingRulesFile(const QString &path);

// ///////////////////////////////////////////////////////////////////
// qDebug overload
// ///////////////////////////////////////////////////////////////////

#if defined(qDebug)
#  undef qDebug
#endif

#define qDebug								\
    for (bool enabled = dtkLoggingCategory::defaultCategory().isEnabled(QtDebugMsg); enabled; enabled = false) \
        QMessageLogger(__FILE__, __LINE__, Q_FUNC_INFO, dtkLoggingCategory::defaultCategory().categoryName()).debug

// ///////////////////////////////////////////////////////////////////
// qWarning overload
// ///////////////////////////////////////////////////////////////////

#if defined(qWarning)
#  undef qWarning
#endif

#define qWarning							\
    for (bool enabled = dtkLoggingCategory::defaultCategory().isEnabled(QtWarningMsg); enabled; enabled = false) \
        QMessageLogger(__FILE__, __LINE__, Q_FUNC_INFO, dtkLoggingCategory::defaultCategory().categoryName()).warning

// ///////////////////////////////////////////////////////////////////
// qCritical overload
// ///////////////////////////////////////////////////////////////////

#if defined(qCritical)
#  undef qCritical
#endif

#define qCritical							\
    for (bool enabled = dtkLoggingCategory::defaultCategory().isEnabled(QtCriticalMsg); enabled; enabled = false) \
        QMessageLogger(__FILE__, __LINE__, Q_FUNC_INFO, dtkLoggingCategory::defaultCategory().categoryName()).critical

// ///////////////////////////////////////////////////////////////////
// Helper macro
// ///////////////////////////////////////////////////////////////////

#define DTK_LOG_CATEGORY(categorytype, categoryname)			\
    namespace {								\
        static dtkLoggingCategory categorytype(categoryname);		\
    }

// ///////////////////////////////////////////////////////////////////
// dtkDebug
// ///////////////////////////////////////////////////////////////////

#define dtkDebug(category)						             \
    for (bool enabled = category.isEnabled(QtDebugMsg); enabled; enabled = false)    \
        QMessageLogger(__FILE__, __LINE__, Q_FUNC_INFO, category.categoryName()).debug()

// ///////////////////////////////////////////////////////////////////
// dtkWarning
// ///////////////////////////////////////////////////////////////////

#define dtkWarning(category)						             \
    for (bool enabled = category.isEnabled(QtWarningMsg); enabled; enabled = false)  \
        QMessageLogger(__FILE__, __LINE__, Q_FUNC_INFO, category.categoryName()).warning()

// ///////////////////////////////////////////////////////////////////
// dtkCritical
// ///////////////////////////////////////////////////////////////////

#define dtkCritical(category)						             \
    for (bool enabled = category.isEnabled(QtCriticalMsg); enabled; enabled = false) \
        QMessageLogger(__FILE__, __LINE__, Q_FUNC_INFO, category.categoryName()).critical()

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
