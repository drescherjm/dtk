/* dtkCompressIOTest.h ---
 *
 * Author: Thibaud Kloczko
 * Created: Tue Jul 23 08:31:17 2013 (+0200)
 */

/* Change Log:
 *
 */

#pragma once

#include <dtkTest>

class dtkCompressIOTestCase : public QObject
{
    Q_OBJECT

public:
             dtkCompressIOTestCase(void);
    virtual ~dtkCompressIOTestCase(void);

private slots:
    void initTestCase(void);
    void init(void);

private slots:
    void testWrite(void);
    void testRead(void);

private slots:
    void cleanupTestCase(void);
    void cleanup(void);
};
