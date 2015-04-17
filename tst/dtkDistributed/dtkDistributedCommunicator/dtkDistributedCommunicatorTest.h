/* dtkDistributedCommunicatorTest.h --- 
 * 
 * Author: Julien Wintz
 * Created: Mon Feb  4 13:58:16 2013 (+0100)
 * Version: 
 * Last-Updated: jeu. févr.  5 16:01:10 2015 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 34
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
    void testPlugin(void);

private slots:
    void cleanupTestCase(void);
    void cleanup(void);
};
