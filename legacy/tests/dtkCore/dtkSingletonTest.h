/* dtkSingletonTest.h ---
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

#ifndef DTKSINGLETONTEST_H
#define DTKSINGLETONTEST_H

#include <dtkCore/dtkTest.h>

class dtkSingletonTestObjectPrivate;

class dtkSingletonTestObject : public QObject
{
    Q_OBJECT

public:
             dtkSingletonTestObject(void);
    virtual ~dtkSingletonTestObject(void);


private slots:
    void initTestCase(void);
    void init(void);
    void cleanup(void);
    void cleanupTestCase(void);

private slots:
    void testSingleton(void);

private:
    dtkSingletonTestObjectPrivate *d;
};

#endif
