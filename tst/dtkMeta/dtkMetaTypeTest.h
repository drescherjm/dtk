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
    void testVariantFromValue(void);

private slots:
    void cleanupTestCase(void);
    void cleanup(void);
};

//
// dtkMetaTypeTest.h ends here
