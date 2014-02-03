/* dtkCompareFloatTest.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Jun 20 13:12:08 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Nov 21 17:24:53 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 13
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
    void testAlmostEqual1(void);
    void testAlmostEqual2(void);

private:
    dtkCompareFloatTestObjectPrivate *d;
};

#endif
