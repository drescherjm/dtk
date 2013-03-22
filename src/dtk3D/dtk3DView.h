/* dtk3DView.h ---
 * 
 * Author: Julien Wintz
 * Created: Fri Mar 22 09:41:33 2013 (+0100)
 * Version: 
 * Last-Updated: Fri Mar 22 11:39:17 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 19
 */

/* Change Log:
 * 
 */

#pragma once

#include <Qt3D/QGLView>

class dtk3DViewPrivate;

class dtk3DView : public QGLView
{
public:
     dtk3DView(QWindow *parent = 0);
    ~dtk3DView(void);

private:
    dtk3DViewPrivate *d;
};
