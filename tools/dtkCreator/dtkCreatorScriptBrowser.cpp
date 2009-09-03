/* dtkCreatorScriptBrowser.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Aug  4 10:07:29 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Aug 31 21:15:34 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 82
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkCreatorScriptBrowser.h"

#include <dtkCore/dtkLog.h>

#include <dtkScript/dtkScriptInterpreter.h>
#include <dtkScript/dtkScriptInterpreterPool.h>
#include <dtkScript/dtkScriptManager.h>

// /////////////////////////////////////////////////////////////////
// dtkCreatorScriptListPrivate
// /////////////////////////////////////////////////////////////////

class dtkCreatorScriptListPrivate
{
public:
    QTextEdit *description;
    QListView *categories;
    QListView *items;
    QDirModel *model;
};

// /////////////////////////////////////////////////////////////////
// dtkCreatorScriptList
// /////////////////////////////////////////////////////////////////

dtkCreatorScriptList::dtkCreatorScriptList(QWidget *parent) : dtkSplitter(parent, true), d(new dtkCreatorScriptListPrivate)
{
    dtkSplitter *splitter = new dtkSplitter(this);

    d->description = new QTextEdit(this);
    d->description->setFrameStyle(QFrame::NoFrame);
    d->description->setAttribute(Qt::WA_MacShowFocusRect, false);
    d->description->setReadOnly(true);

    d->categories = new QListView(splitter);
    d->categories->setFrameStyle(QFrame::NoFrame);
    d->categories->setAttribute(Qt::WA_MacShowFocusRect, false);

    d->items = new QListView(splitter);
    d->items->setFrameStyle(QFrame::NoFrame);
    d->items->setAttribute(Qt::WA_MacShowFocusRect, false);

    splitter->addWidget(d->categories);
    splitter->addWidget(d->items);
    splitter->setSizes(QList<int>() << static_cast<int>(parent->width()*0.5) << static_cast<int>(parent->width()*0.5) );
    splitter->setOrientation(Qt::Horizontal);
    
    this->addWidget(splitter);
    this->addWidget(d->description);
    this->setSizes(QList<int>() << static_cast<int>(parent->height()*0.7) << static_cast<int>(parent->height()*0.3) );
    this->setOrientation(Qt::Vertical);

    d->model = new QDirModel;
    d->model->setFilter(QDir::AllDirs);
    d->categories->setModel(d->model);
    d->categories->setRootIndex(d->model->index(dtkScriptManager::instance()->scriptPath()));
    d->items->setModel(d->model);
    d->items->setRootIndex(d->model->index(dtkScriptManager::instance()->scriptPath() + "/python"));

    connect(d->categories, SIGNAL(clicked(const QModelIndex&)), this, SLOT(onModelIndexClicked(const QModelIndex&)));
    connect(d->items, SIGNAL(clicked(const QModelIndex&)), this, SLOT(onModelIndexClicked(const QModelIndex&)));
    connect(d->categories, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(onModelIndexDoubleClicked(const QModelIndex&)));
    connect(d->items, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(onModelIndexDoubleClicked(const QModelIndex&)));

}

dtkCreatorScriptList::~dtkCreatorScriptList(void)
{
    delete d->description;
    delete d->categories;
    delete d->items;
    delete d;

    d = NULL;
}

void dtkCreatorScriptList::preloadScript(const QString& fileName)
{
    dtkScriptInterpreter *interpreter; int stat;
    if (fileName.endsWith(".py"))
        interpreter = dtkScriptInterpreterPool::instance()->python();
    else if (fileName.endsWith(".tcl"))
        interpreter = dtkScriptInterpreterPool::instance()->tcl();
    else
        return;
    interpreter->load(fileName);
    QString description = interpreter->interpret("description", QStringList(), &stat);

    interpreter->release();

    d->description->setText(description);
}

void dtkCreatorScriptList::loadScript(const QString& fileName)
{
    dtkScriptInterpreter *interpreter; int stat;
    if (fileName.endsWith(".py"))
        interpreter = dtkScriptInterpreterPool::instance()->python();
    else if (fileName.endsWith(".tcl"))
        interpreter = dtkScriptInterpreterPool::instance()->tcl();
    else
        return;
    interpreter->load(fileName);
    interpreter->interpret("init", QStringList(), &stat);
    interpreter->retain();

    // connect(dtkCreatorWidgetFactory::instance(), SIGNAL(interpret(const QString&, int *)), interpreter, SLOT(interpret(const QString&, int *)));

    emit loaded(fileName);
}

void dtkCreatorScriptList::onModelIndexClicked(const QModelIndex& index)
{
    QFileInfo info = d->model->fileInfo(index);

    if(sender() == d->categories) {
        if(info.isDir())
            ; // d->items->setRootIndex(index);
        else
            this->preloadScript(info.absoluteFilePath());
    }
    
    if(sender() == d->items) {
        if(info.isDir()) {
            // d->categories->setRootIndex(index.parent());
            // d->items->setRootIndex(index);
        } else
            this->preloadScript(info.absoluteFilePath());
    }
}

void dtkCreatorScriptList::onModelIndexDoubleClicked(const QModelIndex& index)
{
    QFileInfo info = d->model->fileInfo(index);

    if(sender() == d->categories) {
        if(info.isDir()) {
            d->categories->setRootIndex(index);
            d->items->setRootIndex(index.child(2, 0));
        } else
            this->loadScript(info.absoluteFilePath());
    }
    
    if(sender() == d->items) {
        if(info.isDir()) {
            d->categories->setRootIndex(index);
            d->items->setRootIndex(index.child(2, 0));
        } else
            this->loadScript(info.absoluteFilePath());
    }
}

// /////////////////////////////////////////////////////////////////
// dtkCreatorScriptWidgetPrivate
// /////////////////////////////////////////////////////////////////

class dtkCreatorScriptWidgetPrivate
{
public:
};

// /////////////////////////////////////////////////////////////////
// dtkCreatorScriptWidget
// /////////////////////////////////////////////////////////////////

dtkCreatorScriptWidget::dtkCreatorScriptWidget(QWidget *parent) : QStackedWidget(parent), d(new dtkCreatorScriptWidgetPrivate)
{
    this->layout()->setContentsMargins(0, 0, 0, 0);
}

dtkCreatorScriptWidget::~dtkCreatorScriptWidget(void)
{
    delete d;

    d = NULL;
}

void dtkCreatorScriptWidget::addWidget(QWidget *widget)
{
    if(QWidget *current = this->currentWidget())
        QStackedWidget::removeWidget(current);

    QStackedWidget::addWidget(widget);
    QStackedWidget::setCurrentWidget(widget);
}

// /////////////////////////////////////////////////////////////////
// dtkCreatorScriptBrowserPrivate
// /////////////////////////////////////////////////////////////////

class dtkCreatorScriptBrowserPrivate
{
public:
    dtkCreatorScriptList *list;
    dtkCreatorScriptWidget *widget;
};

// /////////////////////////////////////////////////////////////////
// dtkCreatorScriptBrowser
// /////////////////////////////////////////////////////////////////

dtkCreatorScriptBrowser::dtkCreatorScriptBrowser(QWidget *parent) : dtkSplitter(parent), d(new dtkCreatorScriptBrowserPrivate)
{
    d->list = new dtkCreatorScriptList(this);
    d->widget = new dtkCreatorScriptWidget(this);
    
    this->addWidget(d->list);
    this->addWidget(d->widget);
    this->setOrientation(Qt::Vertical);
    this->setStretchFactor(0, 3);
    this->setStretchFactor(1, 1);
}

dtkCreatorScriptBrowser::~dtkCreatorScriptBrowser(void)
{
    delete d->list;
    delete d->widget;
    delete d;

    d = NULL;
}

QSize dtkCreatorScriptBrowser::sizeHint(void) const
{
    return QSize(200, 1);
}

dtkCreatorScriptList *dtkCreatorScriptBrowser::list(void)
{
    return d->list;
}

dtkCreatorScriptWidget *dtkCreatorScriptBrowser::widget(void)
{
    return d->widget;
}
