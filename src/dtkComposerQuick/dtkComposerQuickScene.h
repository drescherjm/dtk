/* dtkComposerQuickScene.h ---
 * 
 * Author: Julien Wintz
 * Created: Wed Apr 17 10:17:24 2013 (+0200)
 * Version: 
 * Last-Updated: Fri Apr 19 17:13:54 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 31
 */

/* Change Log:
 * 
 */

#pragma once

#include "dtkComposerQuickGraph.h"
#include "dtkComposerQuickNode.h"
#include "dtkComposerQuickStack.h"

#include <dtkComposer>

#include <QtCore>
#include <QtQuick>

class dtkComposerQuickScenePrivate;

class dtkComposerQuickScene : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(dtkComposerQuickGraph *graph READ graph WRITE setGraph)
    Q_PROPERTY(dtkComposerQuickStack *stack READ stack WRITE setStack)
    Q_PROPERTY(QQmlListProperty<dtkComposerQuickNode> nodes READ nodes)

public:
     dtkComposerQuickScene(QObject *parent = 0);
    ~dtkComposerQuickScene(void);

public:
    dtkComposerScene *scene(void);

public:
    dtkComposerQuickGraph *graph(void);
    dtkComposerQuickStack *stack(void);

public:
    QQmlListProperty<dtkComposerQuickNode> nodes(void);

public:
    void setGraph(dtkComposerQuickGraph *graph);
    void setStack(dtkComposerQuickStack *stack);

public:
    static void addNode(QQmlListProperty<dtkComposerQuickNode> *nodes, dtkComposerQuickNode *node);
    static int countNodes(QQmlListProperty<dtkComposerQuickNode> *nodes);
    static void clearNodes(QQmlListProperty<dtkComposerQuickNode> *nodes);
    static dtkComposerQuickNode *nodeAt(QQmlListProperty<dtkComposerQuickNode> *nodes, int index);

public:
    void paint(QPainter *painter);

private:
    dtkComposerQuickScenePrivate *d;
};

QML_DECLARE_TYPE(dtkComposerQuickScene)
