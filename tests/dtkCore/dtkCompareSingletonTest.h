/* dtkCompareSingletonTest.h ---
 *
 * Author: Babette Lekouta
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Jun 20 13:12:08 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Jun 20 14:07:15 2012 (+0200)
 *           By: Lekouta Babette
 *     Update #: 7
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPARESINGLETONTEST_H
#define DTKCOMPARESINGLETONTEST_H

#include <dtkCore/dtkTest.h>

class dtkCompareSingletonTestObjectPrivate;

class dtkCompareSingletonTestObject : public QObject
{
    Q_OBJECT

public:
             dtkCompareSingletonTestObject(void);
    virtual ~dtkCompareSingletonTestObject(void);


private slots:
    void initTestCase(void);
    void init(void);
    void cleanup(void);
    void cleanupTestCase(void);

private slots:
    void testSingleton(void);

private:
    dtkCompareSingletonTestObjectPrivate *d;
};

#endif
