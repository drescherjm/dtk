/* dtkCompareDoubleTest.cpp ---
 *
 * Author: Babette Lekouta
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Wed Jun 20 13:12:23 2012 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Jun 20 14:09:48 2012 (+0200)
 *           By:
 *     Update #:
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKZIPTEST_H
#define DTKZIPTEST_H

#include <dtkCore/dtkTest.h>


class dtkZipTestObjectPrivate;

class dtkZipTestObject : public QObject
{
    Q_OBJECT

public:
             dtkZipTestObject(void);
    virtual ~dtkZipTestObject(void);

private slots:
    void initTestCase(void);
    void init(void);
    void cleanup(void);
    void cleanupTestCase(void);

private slots:
    void basicUnpack(void);
    void symlinks(void);
    void readTest(void);
    void createArchive(void);

private:
    dtkZipTestObjectPrivate *d;
};

#endif
