/* dtkLogView.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Fri Mar  2 15:13:52 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Mar  2 19:08:23 2012 (+0100)
 *           By: Julien Wintz
 *     Update #: 98
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

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

    QTreeWidgetItem *runtime_log = new QTreeWidgetItem(QStringList() << "Runtime log");
    QTreeWidgetItem    *file_log = new QTreeWidgetItem(QStringList() << "File log");
    QTreeWidgetItem *dummy_a_log = new QTreeWidgetItem(QStringList() << "a.log");
    QTreeWidgetItem *dummy_b_log = new QTreeWidgetItem(QStringList() << "b.log");

    file_log->addChild(dummy_a_log);
    file_log->addChild(dummy_b_log);

    this->addTopLevelItem(runtime_log);
    this->addTopLevelItem(file_log);
}

dtkLogViewTree::~dtkLogViewTree(void)
{
    
}

// /////////////////////////////////////////////////////////////////
// dtkLogViewList
// /////////////////////////////////////////////////////////////////

dtkLogViewList::dtkLogViewList(QWidget *parent) : QListView(parent)
{
    this->setAttribute(Qt::WA_MacShowFocusRect, false);
    this->setFrameShape(QFrame::NoFrame);
    this->setRuntime();
}

dtkLogViewList::~dtkLogViewList(void)
{
    
}

void dtkLogViewList::setRuntime(void)
{
    dtkLogger::instance().attachView(this);

    this->setModel(&(this->model));
}

void dtkLogViewList::append(const QString& message)
{
    this->list << message;

    this->model.setStringList(this->list);
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
}

dtkLogView::~dtkLogView(void)
{
    delete d;

    d = NULL;
}
