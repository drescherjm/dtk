/* dtkComposerQuickScene.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Wed Apr 17 10:19:14 2013 (+0200)
 * Version: 
 * Last-Updated: Fri Apr 19 17:16:01 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 114
 */

/* Change Log:
 * 
 */

#include "dtkComposerQuickScene.h"

#include <dtkComposer>

class dtkComposerQuickScenePrivate
{
public:
    void update(void);

public:
    dtkComposerScene *scene;

public:
    dtkComposerQuickGraph *graph;
    dtkComposerQuickScene *q;
    dtkComposerQuickStack *stack;

public:
    QList<dtkComposerQuickNode *> stash;
    QList<dtkComposerQuickNode *> nodes;
};

dtkComposerQuickScene::dtkComposerQuickScene(QObject *parent) : QQuickPaintedItem(0), d(new dtkComposerQuickScenePrivate)
{
    d->q = this;
    d->scene = new dtkComposerScene;

    d->graph = NULL;
    d->stack = NULL;
}

dtkComposerQuickScene::~dtkComposerQuickScene(void)
{
    delete d->scene;
    delete d;
}

dtkComposerScene *dtkComposerQuickScene::scene(void)
{
    return d->scene;
}

dtkComposerQuickGraph *dtkComposerQuickScene::graph(void)
{
    return d->graph;
}

dtkComposerQuickStack *dtkComposerQuickScene::stack(void)
{
    return d->stack;
}

QQmlListProperty<dtkComposerQuickNode> dtkComposerQuickScene::nodes(void)
{
    return QQmlListProperty<dtkComposerQuickNode>(this, &(d->nodes),
					    &dtkComposerQuickScene::addNode,
					    &dtkComposerQuickScene::countNodes,
					    &dtkComposerQuickScene::nodeAt,
					    &dtkComposerQuickScene::clearNodes);
}

void dtkComposerQuickScene::setGraph(dtkComposerQuickGraph *graph)
{
    d->graph = graph;

    d->scene->setGraph(d->graph->graph());

    d->update();
}

void dtkComposerQuickScene::setStack(dtkComposerQuickStack *stack)
{
    d->stack = stack;

    d->scene->setStack(d->stack->stack());

    d->update();
}

void dtkComposerQuickScene::addNode(QQmlListProperty<dtkComposerQuickNode> *nodes, dtkComposerQuickNode *node)
{
    dtkComposerQuickScene *scene = qobject_cast<dtkComposerQuickScene *>(nodes->object);

    if (scene) {
	scene->d->stash << node;
	scene->d->update();
    }
}

int dtkComposerQuickScene::countNodes(QQmlListProperty<dtkComposerQuickNode> *nodes)
{
    dtkComposerQuickScene *scene = qobject_cast<dtkComposerQuickScene *>(nodes->object);

    if (scene) {
	return scene->d->nodes.count();
    }

    return 0;
}

void dtkComposerQuickScene::clearNodes(QQmlListProperty<dtkComposerQuickNode> *nodes)
{
    dtkComposerQuickScene *scene = qobject_cast<dtkComposerQuickScene *>(nodes->object);

    if (scene) {
	return scene->d->nodes.clear();
    }
}

dtkComposerQuickNode *dtkComposerQuickScene::nodeAt(QQmlListProperty<dtkComposerQuickNode> *nodes, int index)
{
    dtkComposerQuickScene *scene = qobject_cast<dtkComposerQuickScene *>(nodes->object);

    if (scene) {
	return scene->d->nodes.at(index);
    }

    return NULL;
}

// ///////////////////////////////////////////////////////////////////
// 
// ///////////////////////////////////////////////////////////////////

void dtkComposerQuickScenePrivate::update(void)
{
    if(!this->graph)
	return;
    
    if(!this->stack)
	return;

    foreach(dtkComposerQuickNode *node, this->stash) {

	dtkComposerStackCommandCreateNode *command = new dtkComposerStackCommandCreateNode;
	command->setFactory(&(dtkComposer::node::factory()));
	command->setScene(this->scene);
	command->setGraph(this->graph->graph());
	command->setParent(this->scene->root());
	command->setPosition(QPointF(0, 0));
	command->setType(node->type());
	command->setName("node");

	this->stack->stack()->push(command);

	node->setNode(command->node()->wrapee());

	this->nodes << node;
    }
    
    this->stash.clear();
}

// ///////////////////////////////////////////////////////////////////
// 
// ///////////////////////////////////////////////////////////////////

void dtkComposerQuickScene::paint(QPainter *painter)
{
    qDebug() << Q_FUNC_INFO;

    d->scene->render(painter, this->contentsBoundingRect());
}
