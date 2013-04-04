/* dtk3DQuickPlugin.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Mon Apr  1 21:47:57 2013 (+0200)
 * Version: 
 * Last-Updated: Wed Apr  3 15:01:23 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 22
 */

/* Change Log:
 * 
 */

#include "dtk3DQuickItem.h"
#include "dtk3DQuickPlugin.h"
#include "dtk3DQuickScene.h"
#include "dtk3DQuickView.h"

#include <dtk3D>

void dtk3DQuickPlugin::registerTypes(const char *uri)
{
    Q_ASSERT(uri == QLatin1String("dtk3DQuick"));

    qmlRegisterType<dtk3DQuickItem>(uri, 1, 0, "Quick3DItem");
    qmlRegisterType<dtk3DQuickScene>(uri, 1, 0, "Quick3DScene");
    qmlRegisterType<dtk3DQuickView>(uri, 1, 0, "Quick3DView");
}
