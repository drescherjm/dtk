/* dtkComposerQuickPlugin.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Wed Apr 17 10:32:32 2013 (+0200)
 * Version: 
 * Last-Updated: Wed Apr 17 10:34:03 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 8
 */

/* Change Log:
 * 
 */

#include "dtkComposerQuickPlugin"
#include "dtkComposerQuickScene"

void dtkComposerQuickPlugin::registerTypes(const char *uri)
{
    Q_ASSERT(uri == QLatin1String("dtkComposerQuick"));

    qmlRegisterType<dtkComposerQuickScene>(uri, 1, 0, "QuickComposerScene");
}
