/* dtk3DViewTest.h ---
 * 
 * Author: Julien Wintz
 * Created: Fri Mar 22 11:35:20 2013 (+0100)
 * Version: 
 * Last-Updated: Fri Mar 22 11:42:21 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 3
 */

/* Change Log:
 * 
 */

#pragma once

#include <dtkTest>

class dtk3DViewTestCasePrivate;

class dtk3DViewTestCase : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase(void);
    void init(void);

private slots:
    void testInstanciation(void);

private slots:
    void cleanupTestCase(void);
    void cleanup(void);
};
