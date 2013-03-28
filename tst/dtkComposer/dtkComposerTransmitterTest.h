/* dtkComposerTransmitterTest.h ---
 * 
 * Author: Thibaud Kloczko
 * Created: Mon Mar 25 11:19:44 2013 (+0100)
 * Version: 
 * Last-Updated: Thu Mar 28 16:40:06 2013 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 14
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
    void testTransmitterLinks(void);

private slots:
    void cleanupTestCase(void);
    void cleanup(void);
};
