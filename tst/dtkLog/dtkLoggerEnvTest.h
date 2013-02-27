/* dtkLoggerEnvTest.h --- 
 * 
 * Author: Julien Wintz
 * Created: Wed Feb 13 15:45:42 2013 (+0100)
 * Version: 
 * Last-Updated: Wed Feb 13 16:22:21 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 42
 */

/* Change Log:
 * 
 */

#include <dtkTest>

// ///////////////////////////////////////////////////////////////////
// Redefine default streams because we don't want to use dtkLogger if
// test application starts up. 
// ///////////////////////////////////////////////////////////////////

#if defined(qDebug)
#  undef qDebug
#endif
#define qDebug QMessageLogger(__FILE__, __LINE__, Q_FUNC_INFO).debug

#if defined(qWarning)
#  undef qWarning
#endif
#define qWarning QMessageLogger(__FILE__, __LINE__, Q_FUNC_INFO).warning

#if defined(qCritical)
#  undef qCritical
#endif
#define qCritical QMessageLogger(__FILE__, __LINE__, Q_FUNC_INFO).critical

// ///////////////////////////////////////////////////////////////////
// Test case
// ///////////////////////////////////////////////////////////////////

class WriteFileThread;

class dtkLoggerEnvTestCase : public QObject
{
    Q_OBJECT

private:
    QStringList logEntries;

private slots:
    void initTestCase(void);

private slots:
    void createQtLoggerFromThread(void);
    void checkFileWatcherTrigger(void);

private slots:
    void cleanupTestCase(void);

private:
    void writeLogRuleFile(void);

private:
    WriteFileThread *pFileWriter;
};

/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the test suite of the Qt Toolkit.
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
