/* dtkComposerTransmitterTest.h ---
 * 
 * Author: Thibaud Kloczko
 * Created: Mon Mar 25 11:19:44 2013 (+0100)
 * Version: 
 * Last-Updated: Wed Apr  3 12:15:39 2013 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 17
 */

/* Change Log:
 * 
 */

#pragma once

#include <dtkTest>

class dtkComposerTransmitterTestCase : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase(void);
    void init(void);

private slots:
    void testAtomicType(void);
    void testComplexType(void);
    void testLinks(void);
    void testProxyLoop(void);

private slots:
    void cleanupTestCase(void);
    void cleanup(void);
};
