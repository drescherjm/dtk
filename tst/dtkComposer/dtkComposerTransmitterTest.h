/* dtkComposerTransmitterTest.h ---
 * 
 * Author: Thibaud Kloczko
 * Created: Mon Mar 25 11:19:44 2013 (+0100)
 * Version: 
 * Last-Updated: Tue Mar 26 14:17:04 2013 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 13
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
    void testTransmitterAtomicType(void);
    void testTransmitterComplexType(void);

private slots:
    void cleanupTestCase(void);
    void cleanup(void);
};
