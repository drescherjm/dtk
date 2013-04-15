/* dtkWidgetsTagCloudTest.cpp ---
 * 
 * Author: Julien Wintz
 * Created: Mon Apr 15 12:09:05 2013 (+0200)
 * Version: 
 * Last-Updated: Mon Apr 15 15:37:08 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 37
 */

/* Change Log:
 * 
 */

#include "dtkWidgetsTagCloudTest.h"

#include <dtkWidgets>

void dtkWidgetsTagCloudTestCase::initTestCase(void)
{

}

void dtkWidgetsTagCloudTestCase::init(void)
{

}

void dtkWidgetsTagCloudTestCase::test(void)
{
    dtkWidgetsTagCloudScope *scope = new dtkWidgetsTagCloudScope;

    dtkWidgetsTagCloud *cloud = new dtkWidgetsTagCloud;
    cloud->setSortingType(dtkWidgetsTagCloud::Alpha);
    cloud->setSortingOrder(dtkWidgetsTagCloud::Asc);
    cloud->setFontSize(18);
    cloud->setFontRange(10);

    dtkWidgetsTagCloudView *view = new dtkWidgetsTagCloudView;

    dtkWidgetsTagCloudController *controller = new dtkWidgetsTagCloudController;
    controller->attach(scope);
    controller->attach(view);
    controller->attach(cloud);
    controller->addItem("name1", "description1", QStringList() << "tag1" << "tag2", "kind", "type");
    controller->addItem("name2", "description2", QStringList() << "tag2" << "tag3", "kind", "type");
    controller->addItem("name3", "description3", QStringList() << "tag2" << "tag4" << "tag6");
    controller->addItem("name4", "description4", QStringList() << "tag5" << "tag6");
    controller->addItem("name5", "description5", QStringList() << "tag5" << "tag6" << "tag2");
    controller->addItem("name6", "description6", QStringList() << "tag7" << "tag8" << "tag9");
    controller->addItem("name7", "description7", QStringList() << "tag3" << "tag1" << "tag9" << "tag2");

    QSplitter *splitter = new QSplitter;
    splitter->addWidget(cloud);
    splitter->addWidget(view);
    splitter->setOrientation(Qt::Vertical);
    splitter->setSizes(QList<int>() << 150 << 350);

    QWidget *widget = new QWidget;

    QVBoxLayout *layout = new QVBoxLayout(widget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(scope);
    layout->addWidget(splitter);

    QMainWindow *window = new QMainWindow;
    window->setCentralWidget(widget);
    window->setUnifiedTitleAndToolBarOnMac(true);
    window->setAttribute(Qt::WA_DeleteOnClose, true);
    window->setWindowTitle("Close window to validate test");
    window->show();
    window->raise();

    QEventLoop loop;
    connect(window, SIGNAL(destroyed()), &loop, SLOT(quit()));
    loop.exec();
}

void dtkWidgetsTagCloudTestCase::cleanupTestCase(void)
{

}

void dtkWidgetsTagCloudTestCase::cleanup(void)
{

}

DTKTEST_MAIN(dtkWidgetsTagCloudTest, dtkWidgetsTagCloudTestCase)
