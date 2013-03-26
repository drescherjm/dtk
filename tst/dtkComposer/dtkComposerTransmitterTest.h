/* dtkComposerTransmitterTest.h ---
 * 
 * Author: Thibaud Kloczko
 * Created: Mon Mar 25 11:19:44 2013 (+0100)
 * Version: 
 * Last-Updated: Mon Mar 25 12:41:54 2013 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 9
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
    void testTransmitter(void);

private slots:
    void cleanupTestCase(void);
    void cleanup(void);
};
