/* dtk3DQuickViewTest.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Mon Apr  1 22:59:13 2013 (+0200)
 * Version: 
 * Last-Updated: Tue Apr  2 10:50:05 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 29
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
    view.setSource(QUrl("qrc:dtk3DQuickViewTest.qml"));
    view.setTitle("dtk3DQuickViewTest");
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
