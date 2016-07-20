/* dtkComposerSceneTest.h ---
 *
 * Author: Julien Wintz
 * Created: Mon Apr 15 10:31:35 2013 (+0200)
 * Version:
 * Last-Updated: Mon Apr 15 10:41:28 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 4
 */

/* Change Log:
 *
 */

#pragma once

#include <dtkTest>

class dtkComposerSceneTestCase : public QObject
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
