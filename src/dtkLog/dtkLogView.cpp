/* dtkLogView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Mar  2 15:13:52 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Mar  5 14:12:28 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 183
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkLog.h"
#include "dtkLogModel.h"
#include "dtkLogView.h"
#include "dtkLogView_p.h"

// /////////////////////////////////////////////////////////////////
// dtkLogViewTree
// /////////////////////////////////////////////////////////////////

dtkLogViewTree::dtkLogViewTree(QWidget *parent) : QTreeWidget(parent)
{
    this->setAttribute(Qt::WA_MacShowFocusRect, false);
    this->setFrameShape(QFrame::HLine);
    this->setHeaderHidden(true);

    this->runtime = new QTreeWidgetItem(QStringList() << "Runtime log");

    this->file = new QTreeWidgetItem(QStringList() << "File log");
    this->file->addChild(new QTreeWidgetItem(QStringList() << dtkLogPath(qApp)));

    this->addTopLevelItem(this->runtime);
    this->addTopLevelItem(this->file);

    connect(this, SIGNAL(itemClicked(QTreeWidgetItem *, int)), this, SLOT(onItemClicked(QTreeWidgetItem *, int)));
}

dtkLogViewTree::~dtkLogViewTree(void)
{
    
}

void dtkLogViewTree::onItemClicked(QTreeWidgetItem *item, int)
{
    if (item == this->runtime)
        emit runtimeClicked();
    else if (item == this->file)
        ;
    else
        emit fileClicked(item->text(0));
}

// /////////////////////////////////////////////////////////////////
// dtkLogViewList
// /////////////////////////////////////////////////////////////////

dtkLogViewList::dtkLogViewList(QWidget *parent) : QListView(parent)
{
    this->model = new dtkLogModel(this);

    this->setAttribute(Qt::WA_MacShowFocusRect, false);
    this->setFrameShape(QFrame::NoFrame);
    this->setRuntime();
}

dtkLogViewList::~dtkLogViewList(void)
{
    qDeleteAll(this->models);
}

void dtkLogViewList::setRuntime(void)
{
    dtkLogger::instance().attachModel(this->model);

    this->setModel(this->model);
}

void dtkLogViewList::setFile(const QString& path)
{
    if (this->models.contains(path))
        this->models.remove(path);

    QFile file(path);

    if(!file.open(QFile::ReadOnly))
        qDebug() << "Unable to read file" << path;

    QString contents = file.readAll();

    file.close();

    QStringListModel *model = new QStringListModel(contents.split("\n"));

    this->setModel(model);

    this->models.insert(path, model);

    // QFileSystemWatcher *watcher = new QFileSystemWatcher(QStringList() << path, this);

    // connect(watcher, SIGNAL(fileChanged(const QString&)), this, SLOT(setFile(const QString&)));
}

// /////////////////////////////////////////////////////////////////
// dtkLogView
// /////////////////////////////////////////////////////////////////

dtkLogView::dtkLogView(QWidget *parent) : QWidget(parent), d(new dtkLogViewPrivate)
{
    d->tree = new dtkLogViewTree(this);
    d->tree->setMaximumWidth(200);

    d->list = new dtkLogViewList(this);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(d->tree);
    layout->addWidget(d->list);

    connect(d->tree, SIGNAL(runtimeClicked()), d->list, SLOT(setRuntime()));
    connect(d->tree, SIGNAL(fileClicked(const QString&)), d->list, SLOT(setFile(const QString&)));
}

dtkLogView::~dtkLogView(void)
{
    delete d;

    d = NULL;
}
