/* dtkDistributedCommunicatorTest.h --- 
 * 
 * Author: Julien Wintz
 * Created: Mon Feb  4 13:58:16 2013 (+0100)
 * Version: 
 * Last-Updated: Fri Feb  8 16:42:55 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 21
 */

/* Change Log:
 * 
 */

#pragma once

#include <dtkTest>

class dtkDistributedCommunicatorTestCase : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase(void);
    void init(void);

private slots:
    void testPluginManager(void);
    void testPluginFactory(void);

private slots:
    void cleanupTestCase(void);
    void cleanup(void);
};
