/* dtkWidgetsTagCloudTest.h ---
 * 
 * Author: Julien Wintz
 * Created: Mon Apr 15 12:08:26 2013 (+0200)
 * Version: 
 * Last-Updated: Mon Apr 15 12:08:56 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 5
 */

/* Change Log:
 * 
 */

#pragma once

#include <dtkTest>

class dtkWidgetsTagCloudTestCase : public QObject
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
