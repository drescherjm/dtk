/* dtk3DView.h ---
 * 
 * Author: Julien Wintz
 * Created: Sat Mar 30 13:40:37 2013 (+0100)
 * Version: 
 * Last-Updated: Tue Apr  2 16:48:43 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 28
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

    void initializeGL(void);
    void initializeGL(QGLPainter *painter);
    void earlyPaintGL(QGLPainter *painter);
    void      paintGL(void);
    void      paintGL(QGLPainter *painter);
    void     resizeGL(int width, int height);

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
