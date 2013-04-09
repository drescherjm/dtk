/* dtk3DEffectTest.h ---
 * 
 * Author: Julien Wintz
 * Created: Mon Apr  8 14:54:18 2013 (+0200)
 * Version: 
 * Last-Updated: Mon Apr  8 22:38:11 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 7
 */

/* Change Log:
 * 
 */

#pragma once

#include <dtkTest>

class dtk3DEffectTestCase : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase(void);
    void init(void);

private slots:
    void test(void);
    void testWireframe(void);

private slots:
    void cleanupTestCase(void);
    void cleanup(void);
};
