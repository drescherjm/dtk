/* dtk3DQuickPlugin.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Mon Apr  1 21:47:57 2013 (+0200)
 * Version: 
 * Last-Updated: Fri Apr  5 13:56:07 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 33
 */

/* Change Log:
 * 
 */

#include "dtk3DQuickItem"
#include "dtk3DQuickMesh"
#include "dtk3DQuickPoint"
#include "dtk3DQuickPlugin"
#include "dtk3DQuickScene"
#include "dtk3DQuickView"

#include <dtk3D>

void dtk3DQuickPlugin::registerTypes(const char *uri)
{
    Q_ASSERT(uri == QLatin1String("dtk3DQuick"));

    qmlRegisterType<dtk3DQuickItem>(uri, 1, 0, "Quick3DItem");
    qmlRegisterType<dtk3DQuickMesh>(uri, 1, 0, "Quick3DMesh");
    qmlRegisterType<dtk3DQuickPoint>(uri, 1, 0, "Quick3DPoint");
    qmlRegisterType<dtk3DQuickScene>(uri, 1, 0, "Quick3DScene");
    qmlRegisterType<dtk3DQuickView>(uri, 1, 0, "Quick3DView");
}
