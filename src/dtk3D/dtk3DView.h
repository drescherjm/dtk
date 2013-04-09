/* dtk3DView.h ---
 * 
 * Author: Julien Wintz
 * Created: Sat Mar 30 13:40:37 2013 (+0100)
 * Version: 
 * Last-Updated: Thu Apr  4 21:57:22 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 91
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
#pragma mark Scene/Item fitting

    void fit(void);
    void fit(const QVector3D& direction);
    void fitFromTop(void);
    void fitFromBack(void);
    void fitFromLeft(void);
    void fitFromFront(void);
    void fitFromRight(void);
    void fitFromBottom(void);

#pragma mark -
#pragma mark Coordinate mapping

public:

    const QPoint mapToScreen(const QVector3D& point);

#pragma mark -
#pragma mark Rendering pipeline
    
    void initializeGL(QGLPainter *painter);
    void earlyPaintGL(QGLPainter *painter);
    void      paintGL(QGLPainter *painter);
    void     resizeGL(int w, int h);

#pragma mark -
#pragma mark Event handling

protected:
    void keyPressEvent(QKeyEvent *event);

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

protected:
    void exposeEvent(QExposeEvent *e);

private:
    dtk3DViewPrivate *d;

private:
    friend class dtk3DQuickView;
};
