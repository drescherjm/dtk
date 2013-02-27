/* dtkDistributedCommunicatorTest.h --- 
 * 
 * Author: Julien Wintz
 * Created: Mon Feb  4 13:58:16 2013 (+0100)
 * Version: 
 * Last-Updated: Mon Feb 11 18:48:40 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 31
 */

/* Change Log:
 * 
 */

#pragma once

#include <dtkTest>

class dtkDistributedCommunicatorTestCasePrivate;

class dtkDistributedCommunicatorTestCase : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase(void);
    void init(void);

private slots:
    void testPluginManager(void);
    void testPluginFactory(void);
    void testPlugin(void);

private slots:
    void cleanupTestCase(void);
    void cleanup(void);
};
