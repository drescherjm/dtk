/* dtk3DViewTest.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Fri Mar 22 11:35:55 2013 (+0100)
 * Version: 
 * Last-Updated: Fri Mar 22 11:49:11 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 23
 */

/* Change Log:
 * 
 */

#include "dtk3DViewTest.h"

#include <dtk3D>

void dtk3DViewTestCase::initTestCase(void)
{

}

void dtk3DViewTestCase::init(void)
{

}

void dtk3DViewTestCase::testInstanciation(void)
{
    dtk3DView view;
    view.resize(800, 600);
    view.show();
    view.raise();

#if 1
    QEventLoop loop;
    loop.exec();
#endif
}

void dtk3DViewTestCase::cleanupTestCase(void)
{

}

void dtk3DViewTestCase::cleanup(void)
{

}

DTKTEST_MAIN_GUI(dtk3DViewTest, dtk3DViewTestCase)
