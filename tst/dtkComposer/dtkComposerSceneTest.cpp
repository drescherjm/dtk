/* dtkComposerSceneTest.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Mon Apr 15 10:32:46 2013 (+0200)
 * Version: 
 * Last-Updated: lun. janv.  5 13:52:47 2015 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 147
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
    scene->setFactory(dtkComposer::node::factory());
    scene->setGraph(graph);
    scene->setStack(stack);

    dtkComposerView *view = new dtkComposerView;
    view->setScene(scene);

    dtkComposerNodeFactoryView *nodes = new dtkComposerNodeFactoryView;
    nodes->setFactory(dtkComposer::node::factory());

    dtkComposerSceneModel *scene_model = new dtkComposerSceneModel;
    scene_model->setScene(scene);

    dtkComposerSceneView *scene_view = new dtkComposerSceneView;
    scene_view->setModel(scene_model);
    scene_view->setScene(scene);

    dtkComposerSceneNodeEditor *editor = new dtkComposerSceneNodeEditor;
    editor->setScene(scene);
    editor->setStack(stack);
    editor->setGraph(graph);

    QSplitter *r_splitter = new QSplitter;
    r_splitter->addWidget(scene_view);
    r_splitter->addWidget(editor);
    r_splitter->setHandleWidth(1);
    r_splitter->setOrientation(Qt::Vertical);

    QSplitter *splitter = new QSplitter;
    splitter->addWidget(nodes);
    splitter->addWidget(view);
    splitter->addWidget(r_splitter);
    splitter->setHandleWidth(1);
    splitter->setWindowTitle("Quit app to validate test");
    splitter->resize(1200, 600);
    splitter->setSizes(QList<int>() << 300 << 1200 - 2*300 << 300);
    splitter->show();
    splitter->raise();

    { // Create a boolean node

	dtkComposerStackCommandCreateNode *command = new dtkComposerStackCommandCreateNode;
	command->setFactory(dtkComposer::node::factory());
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
	command->setFactory(dtkComposer::node::factory());
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
	command->setFactory(dtkComposer::node::factory());
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
	command->setFactory(dtkComposer::node::factory());
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
