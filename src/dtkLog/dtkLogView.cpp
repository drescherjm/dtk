/* dtkLogView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Mar  2 15:13:52 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Apr 24 12:29:06 2012 (+0200)
 *           By: Julien Wintz
 *     Update #: 362
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
// dtkLogViewBar
// /////////////////////////////////////////////////////////////////

dtkLogViewBar::dtkLogViewBar(QWidget *parent) : QFrame(parent)
{
    QPushButton *b_trace = new QPushButton("Trace", this);
    QPushButton *b_debug = new QPushButton("Debug", this);
    QPushButton *b_info  = new QPushButton("Info", this);
    QPushButton *b_warn  = new QPushButton("Warn", this);
    QPushButton *b_error = new QPushButton("Error", this);
    QPushButton *b_fatal = new QPushButton("Fatal", this);

    b_trace->setCheckable(true);
    b_debug->setCheckable(true);
     b_info->setCheckable(true);
     b_warn->setCheckable(true);
    b_error->setCheckable(true);
    b_fatal->setCheckable(true);

    b_trace->setChecked(true);
    b_debug->setChecked(true);
     b_info->setChecked(true);
     b_warn->setChecked(true);
    b_error->setChecked(true);
    b_fatal->setChecked(true);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(b_trace);
    layout->addWidget(b_debug);
    layout->addWidget(b_info);
    layout->addWidget(b_warn);
    layout->addWidget(b_error);
    layout->addWidget(b_fatal);

    connect(b_trace, SIGNAL(clicked(bool)), this, SIGNAL(displayTrace(bool)));
    connect(b_debug, SIGNAL(clicked(bool)), this, SIGNAL(displayDebug(bool)));
    connect(b_info,  SIGNAL(clicked(bool)), this, SIGNAL(displayInfo(bool)));
    connect(b_warn,  SIGNAL(clicked(bool)), this, SIGNAL(displayWarn(bool)));
    connect(b_error, SIGNAL(clicked(bool)), this, SIGNAL(displayError(bool)));
    connect(b_fatal, SIGNAL(clicked(bool)), this, SIGNAL(displayFatal(bool)));
}

dtkLogViewBar::~dtkLogViewBar(void)
{
    
}

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

    this->proxy = new QSortFilterProxyModel(this);
    this->proxy->setFilterKeyColumn(0);

    this->setModel(this->proxy);

    this->setAlternatingRowColors(true);
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

    this->proxy->setSourceModel(this->model);
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

    this->proxy->setSourceModel(model);

    this->models.insert(path, model);

    // QFileSystemWatcher *watcher = new QFileSystemWatcher(QStringList() << path, this);

    // connect(watcher, SIGNAL(fileChanged(const QString&)), this, SLOT(setFile(const QString&)));
}

void dtkLogViewList::setFilter(const QRegExp& expression)
{
    this->proxy->setFilterRegExp(expression);
}

// /////////////////////////////////////////////////////////////////
// dtkLogViewPrivate
// /////////////////////////////////////////////////////////////////

QRegExp dtkLogViewPrivate::expression(void)
{
    if(this->exclude.isEmpty())
        return QRegExp();

    QString patterns;
    foreach(QString pattern, this->exclude)
        patterns.append(QString("%1|").arg(pattern));
    patterns.chop(1);

    return QRegExp(QString("^(?!%1).*").arg(patterns), Qt::CaseSensitive, QRegExp::RegExp2);
}

// /////////////////////////////////////////////////////////////////
// dtkLogView
// /////////////////////////////////////////////////////////////////

dtkLogView::dtkLogView(QWidget *parent) : QWidget(parent), d(new dtkLogViewPrivate)
{
    d->bar = new dtkLogViewBar(this);

    d->tree = new dtkLogViewTree(this);
    d->tree->setMaximumWidth(200);

    d->list = new dtkLogViewList(this);

    QHBoxLayout *h_layout = new QHBoxLayout;
    h_layout->setContentsMargins(0, 0, 0, 0);
    h_layout->setSpacing(0);
    h_layout->addWidget(d->tree);
    h_layout->addWidget(d->list);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(d->bar);
    layout->addLayout(h_layout);

    connect(d->tree, SIGNAL(runtimeClicked()), d->list, SLOT(setRuntime()));
    connect(d->tree, SIGNAL(fileClicked(const QString&)), d->list, SLOT(setFile(const QString&)));

    connect(d->bar, SIGNAL(displayTrace(bool)), this, SLOT(displayTrace(bool)));
    connect(d->bar, SIGNAL(displayDebug(bool)), this, SLOT(displayDebug(bool)));
    connect(d->bar, SIGNAL(displayInfo(bool)),  this, SLOT(displayInfo(bool)));
    connect(d->bar, SIGNAL(displayWarn(bool)),  this, SLOT(displayWarn(bool)));
    connect(d->bar, SIGNAL(displayError(bool)), this, SLOT(displayError(bool)));
    connect(d->bar, SIGNAL(displayFatal(bool)), this, SLOT(displayFatal(bool)));
}

dtkLogView::~dtkLogView(void)
{
    delete d;

    d = NULL;
}

void dtkLogView::displayTrace(bool display)
{
    if(!display)
        d->exclude << "TRACE";
    else
        d->exclude.removeAll("TRACE");

    d->list->setFilter(d->expression());
}

void dtkLogView::displayDebug(bool display)
{
    if(!display)
        d->exclude << "DEBUG";
    else
        d->exclude.removeAll("DEBUG");

    d->list->setFilter(d->expression());
}

void dtkLogView::displayInfo(bool display)
{
    if(!display)
        d->exclude << "INFO";
    else
        d->exclude.removeAll("INFO");

    d->list->setFilter(d->expression());
}

void dtkLogView::displayWarn(bool display)
{
    if(!display)
        d->exclude << "WARN";
    else
        d->exclude.removeAll("WARN");

    d->list->setFilter(d->expression());
}

void dtkLogView::displayError(bool display)
{
    if(!display)
        d->exclude << "ERROR";
    else
        d->exclude.removeAll("ERROR");

    d->list->setFilter(d->expression());
}

void dtkLogView::displayFatal(bool display)
{
    if(!display)
        d->exclude << "FATAL";
    else
        d->exclude.removeAll("FATAL");

    d->list->setFilter(d->expression());
}
