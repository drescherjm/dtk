// Version: $Id$
//
//

// Commentary:
//
//

// Change Log:
//
//

// Code:

#pragma once

#include <dtkTest>

// ///////////////////////////////////////////////////////////////////

class dtkMetaTypeTestCasePrivate;

class dtkMetaTypeTestCase : public QObject
{
    Q_OBJECT

public:
             dtkMetaTypeTestCase(void);
    virtual ~dtkMetaTypeTestCase(void);

private slots:
    void initTestCase(void);
    void init(void);

private slots:
    void testCanConvert(void);
    void testVariantFromValue(void);
    void testClone(void);
    void testCloneContent(void);

private slots:
    void cleanupTestCase(void);
    void cleanup(void);

private:
    dtkMetaTypeTestCasePrivate *d;
};

//
// dtkMetaTypeTest.h ends here
