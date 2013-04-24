/* dtkComposerQuickPlugin.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Wed Apr 17 10:32:32 2013 (+0200)
 * Version: 
 * Last-Updated: Fri Apr 19 11:22:56 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 14
 */

/* Change Log:
 * 
 */

#include "dtkComposerQuickGraph"
#include "dtkComposerQuickPlugin"
#include "dtkComposerQuickScene"
#include "dtkComposerQuickView"

void dtkComposerQuickPlugin::registerTypes(const char *uri)
{
    Q_ASSERT(uri == QLatin1String("dtkComposerQuick"));

    qmlRegisterType<dtkComposerQuickGraph>(uri, 1, 0, "QuickComposerGraph");
    qmlRegisterType<dtkComposerQuickNode>(uri, 1, 0, "QuickComposerNode");
    qmlRegisterType<dtkComposerQuickScene>(uri, 1, 0, "QuickComposerScene");
    qmlRegisterType<dtkComposerQuickStack>(uri, 1, 0, "QuickComposerStack");
    qmlRegisterType<dtkComposerQuickView>(uri, 1, 0, "QuickComposerView");
}
