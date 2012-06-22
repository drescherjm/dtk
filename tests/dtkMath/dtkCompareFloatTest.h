/* dtkCompareFloatTest.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Jun 20 13:12:08 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Jun 20 14:07:15 2012 (+0200)
 *           By: Babette Lekouta
 *     Update #: 7
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCOMPAREFlOATTEST_H
#define DTKCOMPAREFlOATTEST_H

#include <dtkCore/dtkTest.h>

class dtkCompareFloatTestObjectPrivate;

class dtkCompareFloatTestObject : public QObject
{
    Q_OBJECT

public:
             dtkCompareFloatTestObject(void);
    virtual ~dtkCompareFloatTestObject(void);

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
    dtkCompareFloatTestObjectPrivate *d;
};

#endif
