/* dtk3DView.h ---
 * 
 * Author: Julien Wintz
 * Created: Sat Mar 30 13:40:37 2013 (+0100)
 * Version: 
 * Last-Updated: Mon Apr  1 22:32:51 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 11
 */

/* Change Log:
 * 
 */

#pragma once

#include <Qt3D/QGLView>

class dtk3DScene;
class dtk3DViewPrivate;

class dtk3DView : public QGLView
{
    Q_OBJECT

public:
     dtk3DView(QWindow *parent = 0);
    ~dtk3DView(void);

public:
    void setScene(dtk3DScene *scene);

#pragma mark -
#pragma mark Rendering pipeline

public:
    void initializeGL(QGLPainter *painter);
    void      paintGL(QGLPainter *painter);

#pragma mark -
#pragma mark Coordinate mapping

    const QPoint mapToScreen(const QVector3D& point);

#pragma mark -
#pragma mark Event handling

protected:
    void keyPressEvent(QKeyEvent *event);

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    dtk3DViewPrivate *d;
};
