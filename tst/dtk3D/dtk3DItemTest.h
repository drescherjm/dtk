/* dtk3DItemTest.h ---
 * 
 * Author: Julien Wintz
 * Created: Wed Mar 27 14:13:43 2013 (+0100)
 * Version: 
 * Last-Updated: Wed Mar 27 14:14:11 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 3
 */

/* Change Log:
 * 
 */

#pragma once

#include <dtkTest>

class dtk3DItemTestCase : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase(void);
    void init(void);

private slots:
    void testHierarchy(void);

private slots:
    void cleanupTestCase(void);
    void cleanup(void);
};
