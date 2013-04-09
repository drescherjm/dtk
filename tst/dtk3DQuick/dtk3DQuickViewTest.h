/* dtk3DQuickTest.h.in ---
 * 
 * Author: Julien Wintz
 * Created: Mon Apr  1 23:13:43 2013 (+0200)
 * Version: 
 * Last-Updated: Tue Apr  2 09:52:39 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 7
 */

/* Change Log:
 * 
 */

#pragma once

#include <dtkTest>

class dtk3DQuickViewTestCase : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase(void);
    void init(void);

private slots:
    void testView(void);

private slots:
    void cleanupTestCase(void);
    void cleanup(void);
};
