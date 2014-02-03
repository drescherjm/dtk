/* dtkGraphTest.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2013 - Nicolas Niclausse, Inria.
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKGRAPHTEST_H
#define DTKGRAPHTEST_H

#include <dtkCore/dtkTest.h>

class dtkGraphTestObjectPrivate;

class dtkGraphTestObject : public QObject
{
    Q_OBJECT

public:
             dtkGraphTestObject(void);
    virtual ~dtkGraphTestObject(void);

private slots:
    void initTestCase(void);
    void init(void);
    void cleanup(void);
    void cleanupTestCase(void);

private slots:
    void testSort(void);
    void testSubGraph(void);

private:
    dtkGraphTestObjectPrivate *d;
};

#endif
