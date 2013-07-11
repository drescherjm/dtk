/* dtkComposerQuickPlugin.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Wed Apr 17 10:32:32 2013 (+0200)
 * Version: 
 * Last-Updated: Wed Apr 24 10:52:18 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 17
 */

/* Change Log:
 * 
 */

#include "dtkComposerQuickPlugin"

void dtkComposerQuickPlugin::registerTypes(const char *uri)
{
    Q_ASSERT(uri == QLatin1String("dtkComposerQuick"));
}
