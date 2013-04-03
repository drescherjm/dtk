/* dtk3DView.h ---
 * 
 * Author: Julien Wintz
 * Created: Sat Mar 30 13:40:37 2013 (+0100)
 * Version: 
 * Last-Updated: Wed Apr  3 10:05:06 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 40
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
    
    void initializeGL(void) { QGLView::initializeGL(); }
    void initializeGL(QGLPainter *painter);
    void earlyPaintGL(QGLPainter *painter) { QGLView::earlyPaintGL(painter); }
    void      paintGL(void) { QGLView::paintGL(); }
    void      paintGL(QGLPainter *painter);
    void     resizeGL(int w, int h);

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

private:
    friend class dtk3DQuickView;
};
