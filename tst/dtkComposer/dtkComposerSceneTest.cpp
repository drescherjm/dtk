/* dtkComposerSceneTest.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Mon Apr 15 10:32:46 2013 (+0200)
 * Version: 
 * Last-Updated: Mon Apr 15 11:41:58 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 107
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
    dtkComposerGraph *graph = new dtkComposerGraph;
    dtkComposerStack *stack = new dtkComposerStack;

    dtkComposerScene *scene = new dtkComposerScene;
    scene->setFactory(&(dtkComposer::node::factory()));
    scene->setGraph(graph);
    scene->setStack(stack);

    dtkComposerView *view = new dtkComposerView;
    view->setScene(scene);
    view->setWindowTitle("Quit app to validate test");
    view->resize(800, 600);
    view->show();
    view->raise();

    { // Create a boolean node

	dtkComposerStackCommandCreateNode *command = new dtkComposerStackCommandCreateNode;
	command->setFactory(&(dtkComposer::node::factory()));
	command->setScene(scene);
	command->setGraph(graph);
	command->setParent(scene->root());
	command->setPosition(QPointF(-250, 50));
	command->setType("boolean");
	command->setName("node");

	stack->push(command);
    }

    { // Create another boolean node

	dtkComposerStackCommandCreateNode *command = new dtkComposerStackCommandCreateNode;
	command->setFactory(&(dtkComposer::node::factory()));
	command->setScene(scene);
	command->setGraph(graph);
	command->setParent(scene->root());
	command->setPosition(QPointF(-250, -50));
	command->setType("boolean");
	command->setName("node");
            
	stack->push(command);
    }

    { // Create another boolean node

	dtkComposerStackCommandCreateNode *command = new dtkComposerStackCommandCreateNode;
	command->setFactory(&(dtkComposer::node::factory()));
	command->setScene(scene);
	command->setGraph(graph);
	command->setParent(scene->root());
	command->setPosition(QPointF(250, 0));
	command->setType("boolean");
	command->setName("node");
            
	stack->push(command);
    }

    { // Create a boolean operator node

	dtkComposerStackCommandCreateNode *command = new dtkComposerStackCommandCreateNode;
	command->setFactory(&(dtkComposer::node::factory()));
	command->setScene(scene);
	command->setGraph(graph);
	command->setParent(scene->root());
	command->setPosition(QPointF(0, 0));
	command->setType("and");
	command->setName("node");
            
	stack->push(command);
    }

    // --

    QEventLoop loop;
    loop.exec();

    // --

    delete graph;
    delete stack;
    delete scene;
    delete view;
}

void dtkComposerSceneTestCase::cleanupTestCase(void)
{

}

void dtkComposerSceneTestCase::cleanup(void)
{

}

DTKTEST_MAIN(dtkComposerSceneTest, dtkComposerSceneTestCase)
