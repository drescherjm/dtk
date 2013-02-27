/* dtkLoggerTest.h --- 
 * 
 * Author: Julien Wintz
 * Created: Mon Feb 11 23:20:58 2013 (+0100)
 * Version: 
 * Last-Updated: Wed Feb 13 16:02:54 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 33
 */

/* Change Log:
 * 
 */

#pragma once

#include <dtkTest>

class dtkLoggerTestCase : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase(void);

private slots:
    void checkNoCategoryLogActive(void);
    void checkLegacyLogs(void);
    void checkLegacyMessageLogger(void);

private slots:
    void checkFiltering(void);
    void checkLogWithCategoryObject(void);
    void checkEmptyCategoryName(void);
    void checkMultithreading(void);

private slots:
    void writeCategoryLogs(void);

private slots:
    void cleanupTestCase(void);
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
