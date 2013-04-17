/* dtkComposerQuickViewTest.h ---
 * 
 * Author: Julien Wintz
 * Created: Wed Apr 17 10:55:32 2013 (+0200)
 * Version: 
 * Last-Updated: Wed Apr 17 10:55:51 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 2
 */

/* Change Log:
 * 
 */

#pragma once

#include <dtkTest>

class dtkComposerQuickViewTestCase : public QObject
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
