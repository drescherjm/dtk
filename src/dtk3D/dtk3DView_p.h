/* dtk3DView_p.h ---
 * 
 * Author: Julien Wintz
 * Created: Thu Apr  4 21:59:33 2013 (+0200)
 * Version: 
 * Last-Updated: Thu Apr  4 22:00:02 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 4
 */

/* Change Log:
 * 
 */

#pragma once

class dtk3DItem;
class dtk3DScene;

class dtk3DViewPrivate
{
public:
    dtk3DItem *current;

public:
    dtk3DScene *scene;

public:
    bool embedded;
};
