/* dtk3DView.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Fri Mar 22 09:41:43 2013 (+0100)
 * Version: 
 * Last-Updated: Fri Mar 22 10:30:02 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 4
 */

/* Change Log:
 * 
 */

#include "dtk3DView.h"

class dtk3DViewPrivate
{
public:
};

dtk3DView::dtk3DView(QWindow *parent) : QGLView(parent), d(new dtk3DViewPrivate)
{

}

dtk3DView::~dtk3DView(void)
{
    delete d;

    d = NULL;
}
