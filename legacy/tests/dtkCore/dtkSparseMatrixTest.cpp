/* dtkSparseMatrixTest.cpp ---
 * 
 * Author: Thibaud Kloczko
 * Created: mar. janv. 28 16:55:02 2014 (+0100)
 */

/* Change Log:
 * 
 */

#include "dtkSparseMatrixTest.h"

#include <dtkConfig.h>

#include <dtkCore/dtkSparseMatrix.h>
#include <dtkCore/dtkGlobal.h>

#include <QtCore>

// /////////////////////////////////////////////////////////////////
// Helper classes
// /////////////////////////////////////////////////////////////////

// ///////////////////////////////////////////////////////////////////
// 
// ///////////////////////////////////////////////////////////////////

dtkSparseMatrixTestObject::dtkSparseMatrixTestObject(void)
{
}

dtkSparseMatrixTestObject::~dtkSparseMatrixTestObject(void)
{

}

void dtkSparseMatrixTestObject::initTestCase(void)
{

}

void dtkSparseMatrixTestObject::init(void)
{

}

void dtkSparseMatrixTestObject::cleanup(void)
{

}

void dtkSparseMatrixTestObject::cleanupTestCase(void)
{

}

void dtkSparseMatrixTestObject::testCreate(void)
{
    // 
    qlonglong rows = 10;
    qlonglong cols = 10;
    qlonglong rows_start[] = {0, 2, 4, 7, 9, 12, 15, 17, 19, 22};
    qlonglong nnz = 25;
    qlonglong rows_ids[] = {0, 0, 1, 1, 2, 2, 2, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 7, 7, 8, 8, 8, 9, 9, 9};
    qlonglong cols_ids[] = {0, 5, 0, 1, 1, 2, 3, 3, 7, 4, 5, 6, 4, 5, 7, 1, 6, 4, 7, 0, 2, 8, 3, 7, 9};
    double array[nnz];
    for (qlonglong i = 0; i < nnz; ++i)
        array[i] = 17 * (i + 1) / 3.14159;
    
    //
    dtkSparseMatrix<double> matrix_csr(new dtkSparseMatrixHandlerCsr<double>());
    dtkSparseMatrix<double> matrix_hash(new dtkSparseMatrixHandlerHash<double>());

    //
    matrix_csr.resize(rows, cols);
    QVERIFY((rows == matrix_csr.rowCount()) && (cols == matrix_csr.colCount()));

    //
    matrix_csr.reserve(25);
    for (qlonglong i = 0; i < nnz; ++i) {
        matrix_csr.append(rows_ids[i], cols_ids[i], array[i]);
        matrix_hash.append(rows_ids[i], cols_ids[i], array[i]);
    }

    dtkSparseMatrix<double>::const_iterator it = matrix_csr.cbegin();
    dtkSparseMatrix<double>::const_iterator end = matrix_csr.cend();
    while (it != end) {
        qlonglong pos = it.pos();
        QVERIFY((*it) == array[pos]);
        QPair<qlonglong, qlonglong> coordinates = it.coordinates();
        QVERIFY(coordinates.first == rows_ids[pos] && coordinates.second == cols_ids[pos]);
        ++it;
    }

    it = matrix_hash.cbegin();
    end = matrix_hash.cend();
    while (it != end) {
        qlonglong pos = it.pos();
        QVERIFY((*it) == array[pos]);
        QPair<qlonglong, qlonglong> coordinates = it.coordinates();
        QVERIFY(coordinates.first == rows_ids[pos] && coordinates.second == cols_ids[pos]);
        ++it;
    }
    
}

DTKTEST_NOGUI_MAIN(dtkSparseMatrixTest, dtkSparseMatrixTestObject)

// ///////////////////////////////////////////////////////////////////
// Credits
// ///////////////////////////////////////////////////////////////////

/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt3D module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/
