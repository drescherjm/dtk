/* dtk3DShaderTest.h ---
 * 
 * Author: Julien Wintz
 * Created: Fri Apr  5 19:25:15 2013 (+0200)
 * Version: 
 * Last-Updated: Mon Apr  8 10:46:42 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 4
 */

/* Change Log:
 * 
 */

#pragma once

#include <dtkTest>

class dtk3DShaderTestCase : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase(void);
    void init(void);

private slots:
    void test(void);

private slots:
    void cleanupTestCase(void);
    void cleanup(void);
};
