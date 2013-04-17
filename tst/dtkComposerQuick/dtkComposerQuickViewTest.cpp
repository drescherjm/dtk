/* dtkComposerQuickViewTest.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Wed Apr 17 10:55:59 2013 (+0200)
 * Version: 
 * Last-Updated: Wed Apr 17 11:37:06 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 7
 */

/* Change Log:
 * 
 */

#include "dtkComposerQuickViewTest.h"

#include <dtkComposerQuick>

#include <QtCore>
#include <QtGui>
#include <QtQuick>

void dtkComposerQuickViewTestCase::initTestCase(void)
{

}

void dtkComposerQuickViewTestCase::init(void)
{

}

void dtkComposerQuickViewTestCase::testView(void)
{
    QQuickView view;
    view.engine()->addImportPath(dtkComposerQuickImportPath);
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("qrc:dtkComposerQuickViewTest/dtkComposerQuickViewTest.qml"));
    view.setTitle("Quit app to validate test");
    view.show();

    QEventLoop loop;
    loop.exec();
}

void dtkComposerQuickViewTestCase::cleanupTestCase(void)
{

}

void dtkComposerQuickViewTestCase::cleanup(void)
{

}

DTKTEST_MAIN(dtkComposerQuickViewTest, dtkComposerQuickViewTestCase)
