/* dtkArrayTest.h ---
 *
 * Author: Thibaud Kloczko
 * Created: Tue Jul 23 08:31:17 2013 (+0200)
 */

/* Change Log:
 *
 */

#pragma once

#include <dtkTest>

class dtkStaticArrayTestCase : public QObject
{
    Q_OBJECT

public:
     dtkStaticArrayTestCase(void);
    ~dtkStaticArrayTestCase(void);

private slots:
    void initTestCase(void);
    void init(void);

private slots:
    void testCreate(void);
    void testAlignment(void);
    void testFill(void);
    void testAssignement(void);
    void testSetAt(void);
    void testAt(void);
    void testIterate(void);
    void testComparison(void);

private slots:
    void cleanupTestCase(void);
    void cleanup(void);
};
