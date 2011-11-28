/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue May 12 10:34:30 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Nov 28 23:55:04 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 48
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include  <QtGui>
#include <dtkGui/dtkTagCloud.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    dtkTagScope *scope = new dtkTagScope;

    dtkTagCloud *cloud = new dtkTagCloud;
    cloud->setSortingType(dtkTagCloud::Alpha);
    cloud->setSortingOrder(dtkTagCloud::Asc);
    cloud->setFontSize(18);
    cloud->setFontRange(10);

    dtkItemView *view = new dtkItemView;
    view->setItemDelegate(new dtkItemViewDelegate(view));

    dtkTagController *controller = new dtkTagController;
    controller->attach(scope);
    controller->attach(view);
    controller->attach(cloud);
    controller->addItem("name1", "description1", QStringList() << "tag1" << "tag2");
    controller->addItem("name2", "description2", QStringList() << "tag2" << "tag3");
    controller->addItem("name3", "description3", QStringList() << "tag2" << "tag4" << "tag6");
    controller->addItem("name4", "description4", QStringList() << "tag5" << "tag6");
    controller->addItem("name5", "description5", QStringList() << "tag5" << "tag6" << "tag2");
    controller->addItem("name6", "description6", QStringList() << "tag7" << "tag8" << "tag9");
    controller->addItem("name7", "description7", QStringList() << "tag3" << "tag1" << "tag9" << "tag2");

    QSplitter *splitter = new QSplitter;
    splitter->addWidget(cloud);
    splitter->addWidget(view);
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
    window->show();
    window->raise();

    int status = a.exec();

    delete window;

    return status;
}
