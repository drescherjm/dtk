/* dtkCreatorScriptBrowser.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Aug  4 10:07:29 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Aug  4 11:26:13 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 25
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

    // Initialization ---
    QDir dir(QApplication::applicationDirPath());
#ifdef Q_WS_MAC
    dir.cdUp();
    dir.cdUp();
    dir.cdUp();
#elif defined(Q_WS_WIN)
	dir.cdUp();
#endif
    dir.cdUp();
    if(!dir.cd("scripts"))
        dtkDebug() << "No script found in " << dir.absolutePath();

    d->model = new QDirModel;
    d->categories->setModel(d->model);
    d->categories->setRootIndex(d->model->index(dir.absolutePath()));
    d->items->setModel(d->model);
    d->items->setRootIndex(d->model->index(dir.absolutePath()));

    connect(d->categories, SIGNAL(clicked(const QModelIndex&)), d->items, SLOT(setRootIndex(const QModelIndex&)));

    connect(d->items, SIGNAL(clicked(const QModelIndex&)), this, SLOT(preloadScript(const QModelIndex&)));
    connect(d->items, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(loadScript(const QModelIndex&)));
}

dtkCreatorScriptList::~dtkCreatorScriptList(void)
{
    delete d->description;
    delete d->categories;
    delete d->items;
    delete d;

    d = NULL;
}

void dtkCreatorScriptList::preloadScript(const QModelIndex& index)
{
    QString fileName = d->model->filePath(index);
    int stat;
    
    dtkScriptInterpreter *interpreter;
    if (fileName.endsWith(".py"))
        interpreter = dtkScriptInterpreterPool::instance()->python();
    else if (fileName.endsWith(".tcl"))
        interpreter = dtkScriptInterpreterPool::instance()->tcl();
    interpreter->load(fileName);
    QString description = interpreter->interpret("description", QStringList(), &stat);

    // interpreter->release();

    d->description->setText(description);
}

void dtkCreatorScriptList::loadScript(const QModelIndex& index)
{
    int stat;
    QString fileName = d->model->filePath(index);

    dtkScriptInterpreter *interpreter;
    if (fileName.endsWith(".py"))
        interpreter = dtkScriptInterpreterPool::instance()->python();
    else if (fileName.endsWith(".tcl"))
        interpreter = dtkScriptInterpreterPool::instance()->tcl();
    interpreter->load(fileName);
    interpreter->interpret("init", QStringList(), &stat);
    interpreter->retain();

    // connect(dtkCreatorWidgetFactory::instance(), SIGNAL(interpret(const QString&, int *)), interpreter, SLOT(interpret(const QString&, int *)));

    emit loaded(fileName);
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
    this->setSizes(QList<int>() << static_cast<int>(parent->height()*0.35) << static_cast<int>(parent->height()*0.65));
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
