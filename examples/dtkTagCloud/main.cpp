/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue May 12 10:34:30 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Tue May 12 16:08:03 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 4
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtGui>

#include <dtkGui/dtkSplitter.h>
#include <dtkGui/dtkTagCloud.h>

static QString cloud_stylesheet =
"body      { color: rgb(99, 99,  99); background:#ffffff; }"
"a:link    { color: rgb(18, 89, 199); text-decoration:none; }"
"a:active  { color: rgb(81, 86, 151); text-decoration:none; }"
"a:hover   { color: rgb(81, 86, 151); text-decoration:underline; }";

static QString scope_stylesheet =
"body { border-bottom: 1px solid rgb(145, 145, 145); }";

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    dtkTagScope *scope = new dtkTagScope;
    scope->setStyleSheet(scope_stylesheet);

    dtkTagCloud *cloud = new dtkTagCloud;
    cloud->setSortingType(dtkTagCloud::Alpha);
    cloud->setSortingOrder(dtkTagCloud::Asc);
    cloud->setFontSize(18);
    cloud->setFontRange(10);
    cloud->setStyleSheet(cloud_stylesheet);

    dtkItemView *view = new dtkItemView;

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

    dtkSplitter *splitter = new dtkSplitter;
    splitter->addWidget(view);
    splitter->addWidget(cloud);
    splitter->setSizes(QList<int>() << 350 << 150);

    QWidget widget;
    QVBoxLayout layout(&widget);
    layout.setContentsMargins(0, 0, 0, 0);
    layout.setSpacing(0);
    layout.addWidget(scope);
    layout.addWidget(splitter);
    widget.setWindowTitle("Items & tags");
    widget.show();
    widget.resize(500, 245);

    return a.exec();
}
