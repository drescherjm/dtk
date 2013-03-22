/* dtk3DView.h ---
 * 
 * Author: Julien Wintz
 * Created: Fri Mar 22 09:41:33 2013 (+0100)
 * Version: 
 * Last-Updated: Fri Mar 22 14:34:35 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 30
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
public:
     dtk3DView(QWindow *parent = 0);
    ~dtk3DView(void);

#pragma mark -
#pragma mark Scene management
    
    void setScene(dtk3DScene *scene);

protected:
    void initializeGL(QGLPainter *painter);
    void      paintGL(QGLPainter *painter);

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    dtk3DViewPrivate *d;
};
