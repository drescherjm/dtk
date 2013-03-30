/* dtk3DScene.h ---
 * 
 * Author: Julien Wintz
 * Created: Sat Mar 30 13:44:59 2013 (+0100)
 * Version: 
 * Last-Updated: Sat Mar 30 13:45:36 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 7
 */

/* Change Log:
 * 
 */

#pragma once

#include <Qt3D/QGLAbstractScene>
#include <Qt3D/QGLSceneNode>
#include <Qt3D/QGLView>

class dtk3DItem;
class dtk3DScenePrivate;

class dtk3DScene : public QGLAbstractScene
{
    Q_OBJECT

public:
     dtk3DScene(QObject *parent = 0);
    ~dtk3DScene(void);

public:
    void    addItem(dtk3DItem *item);
    void removeItem(dtk3DItem *item);

public:
    void    addNode(QGLSceneNode *node);
    void removeNode(QGLSceneNode *node);

public:
    QGLSceneNode *mainNode(void) const;

public:
     QList<QObject *> objects(void) const;

public:
     void dump(void);
     void dump(QGLSceneNode *node);

public:
    void initialize(QGLPainter *painter, QGLView *view);
    void      paint(QGLPainter *painter, QGLView *view);

private:
     dtk3DScenePrivate *d;
};
