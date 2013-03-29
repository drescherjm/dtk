/* dtk3DScene.h ---
 * 
 * Author: Julien Wintz
 * Created: Fri Mar 22 11:50:58 2013 (+0100)
 * Version: 
 * Last-Updated: Wed Mar 27 16:11:35 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 42
 */

/* Change Log:
 * 
 */

#pragma once

#include <Qt3D/QGLPainter>
#include <Qt3D/QGLView>

class dtk3DScenePrivate;

class dtk3DScene : public QObject
{
    Q_OBJECT

public:
     dtk3DScene(QObject *parent = 0);
    ~dtk3DScene(void);

#pragma mark -
#pragma mark Geometric attributes
    
    QBox3D boundingBox(void);

#pragma mark -
#pragma mark Painting

    void initialize(QGLView *view, QGLPainter *painter);
    void      paint(QGLView *view, QGLPainter *painter);

private:
    dtk3DScenePrivate *d;
};
