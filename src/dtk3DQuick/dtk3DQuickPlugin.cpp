/* dtk3DQuickPlugin.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Mon Apr  1 21:47:57 2013 (+0200)
 * Version: 
 * Last-Updated: Tue Apr  2 11:01:11 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 15
 */

/* Change Log:
 * 
 */

#include "dtk3DQuickPlugin.h"
#include "dtk3DQuickView.h"

void dtk3DQuickPlugin::registerTypes(const char *uri)
{
    Q_ASSERT(uri == QLatin1String("dtk3DQuick"));

    qmlRegisterType<dtk3DQuickView>(uri, 1, 0, "Quick3DView");
}
