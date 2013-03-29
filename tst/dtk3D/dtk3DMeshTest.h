/* dtk3DMeshTest.h ---
 * 
 * Author: Julien Wintz
 * Created: Mon Mar 25 12:56:35 2013 (+0100)
 * Version: 
 * Last-Updated: Wed Mar 27 13:22:47 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 7
 */

/* Change Log:
 * 
 */

#pragma once

#include <dtkTest>

class dtk3DMeshTestCase : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase(void);
    void init(void);

private slots:
    void testGeometry(void);

private slots:
    void cleanupTestCase(void);
    void cleanup(void);
};
