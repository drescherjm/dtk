/* dtkComposerQuickPlugin.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Wed Apr 17 10:32:32 2013 (+0200)
 * Version: 
 * Last-Updated: Wed Apr 17 11:02:16 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 10
 */

/* Change Log:
 * 
 */

#include "dtkComposerQuickPlugin"
#include "dtkComposerQuickScene"
#include "dtkComposerQuickView"

void dtkComposerQuickPlugin::registerTypes(const char *uri)
{
    Q_ASSERT(uri == QLatin1String("dtkComposerQuick"));

    qmlRegisterType<dtkComposerQuickScene>(uri, 1, 0, "QuickComposerScene");
    qmlRegisterType<dtkComposerQuickView>(uri, 1, 0, "QuickComposerView");
}
