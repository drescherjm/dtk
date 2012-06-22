/* dtkCompareDoubleTest.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Jun 20 13:12:08 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Jun 20 14:07:15 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 7
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
    void testCompareAll(void);
    void testCompare2sComplement(void);
    void testCompareFinal(void);

private:
    dtkCompareDoubleTestObjectPrivate *d;
};

#endif
