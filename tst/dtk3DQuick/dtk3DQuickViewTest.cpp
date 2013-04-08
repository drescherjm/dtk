/* dtk3DQuickViewTest.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Mon Apr  1 22:59:13 2013 (+0200)
 * Version: 
 * Last-Updated: Mon Apr  8 22:16:49 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 35
 */

/* Change Log:
 * 
 */

#include "dtk3DQuickViewTest.h"

#include <dtk3DQuick>

#include <QtCore>
#include <QtGui>
#include <QtQuick>

void dtk3DQuickViewTestCase::initTestCase(void)
{

}

void dtk3DQuickViewTestCase::init(void)
{

}

void dtk3DQuickViewTestCase::testView(void)
{
    QQuickView view;
    view.engine()->addImportPath(dtk3DQuickImportPath);
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("qrc:dtk3DQuickViewTest/dtk3DQuickViewTest.qml"));
    view.setTitle("Quit app to validate test");
    view.show();

    QEventLoop loop;
    loop.exec();
}

void dtk3DQuickViewTestCase::cleanupTestCase(void)
{

}

void dtk3DQuickViewTestCase::cleanup(void)
{

}

DTKTEST_MAIN_GUI(dtk3DQuickViewTest, dtk3DQuickViewTestCase)
