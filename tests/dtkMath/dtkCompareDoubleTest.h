/* dtkCompareDoubleTest.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Jun 20 13:12:08 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Nov 21 17:25:01 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 13
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPAREDOUBLETEST_H
#define DTKCOMPAREDOUBLETEST_H

#include <dtkCore/dtkTest.h>

class dtkCompareDoubleTestObjectPrivate;

class dtkCompareDoubleTestObject : public QObject
{
    Q_OBJECT

public:
             dtkCompareDoubleTestObject(void);
    virtual ~dtkCompareDoubleTestObject(void);

private slots:
    void initTestCase(void);
    void init(void);
    void cleanup(void);
    void cleanupTestCase(void);

private slots:
    void testAlmostEqual1(void);
    void testAlmostEqual2(void);

private:
    dtkCompareDoubleTestObjectPrivate *d;
};

#endif
