/* dtk3DQuickPlugin.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Mon Apr  1 21:47:57 2013 (+0200)
 * Version: 
 * Last-Updated: Mon Apr  1 21:48:28 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 7
 */

/* Change Log:
 * 
 */

#include "dtk3DQuickPlugin.h"

void dtk3DQuickPlugin::registerTypes(const char *uri)
{
    Q_ASSERT(uri == QLatin1String("dtk3DQuick"));

    // qmlRegisterType<qtrCanvas>(uri, 1, 0, "QtrCanvas");
}
