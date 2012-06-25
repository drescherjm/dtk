/* dtkSingletonTest.h ---
 *
 * Author: Babette Lekouta
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Jun 25 13:12:08 2012 (+0200)
 * Version: $Id$
 * Last-Updated:
 *           By:
 *     Update #:
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKSMARTPOINTERTEST_H
#define DTKSMARTPOINTERTEST_H

#include <dtkCore/dtkTest.h>

class dtkSmartPointerTestObjectPrivate;

class dtkSmartPointerTestObject : public QObject
{
    Q_OBJECT

public:
             dtkSmartPointerTestObject(void);
    virtual ~dtkSmartPointerTestObject(void);


private slots:
    void initTestCase(void);
    void init(void);
    void cleanup(void);
    void cleanupTestCase(void);

private slots:
    void testSmartPointer(void);
    void testSmartPointerSet(void);
    void testSmartPointerHash(void);
    void testSmartPointerVector(void);


private:
    dtkSmartPointerTestObjectPrivate *d;
};

#endif
