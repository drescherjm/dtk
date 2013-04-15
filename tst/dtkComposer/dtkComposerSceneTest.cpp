/* dtkComposerSceneTest.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Mon Apr 15 10:32:46 2013 (+0200)
 * Version: 
 * Last-Updated: Mon Apr 15 10:48:49 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 26
 */

/* Change Log:
 * 
 */

#include "dtkComposerSceneTest.h"

#include <dtkComposer>

void dtkComposerSceneTestCase::initTestCase(void)
{

}

void dtkComposerSceneTestCase::init(void)
{

}

void dtkComposerSceneTestCase::test(void)
{
    dtkComposerGraph graph;
    dtkComposerStack stack;

    dtkComposerScene scene;
    scene.setFactory(&(dtkComposer::node::factory()));
    scene.setGraph(&graph);
    scene.setStack(&stack);

    dtkComposerView view;
    view.setScene(&scene);
    view.setWindowTitle("Quit app to validate test");
    view.resize(800, 600);
    view.show();
    view.raise();

    QEventLoop loop;
    loop.exec();
}

void dtkComposerSceneTestCase::cleanupTestCase(void)
{

}

void dtkComposerSceneTestCase::cleanup(void)
{

}

DTKTEST_MAIN(dtkComposerSceneTest, dtkComposerSceneTestCase)
