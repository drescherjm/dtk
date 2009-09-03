/* dtkCreatorScriptBrowser.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Aug  4 10:07:29 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Sep  3 18:59:35 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 145
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkCreatorScriptBrowser.h"
#include "dtkCreatorWidgetFactory.h"

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
    QColumnView *view;
    QDirModel *model;
};

// /////////////////////////////////////////////////////////////////
// dtkCreatorScriptList
// /////////////////////////////////////////////////////////////////

dtkCreatorScriptList::dtkCreatorScriptList(QWidget *parent) : QWidget(parent), d(new dtkCreatorScriptListPrivate)
{
    d->description = new QTextEdit;
    d->description->setFrameStyle(QFrame::NoFrame);
    d->description->setAttribute(Qt::WA_MacShowFocusRect, false);
    d->description->setReadOnly(true);

    d->model = new QDirModel;
    d->model->setFilter(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Files);

    d->view = new QColumnView(this);
    d->view->setFrameStyle(QFrame::NoFrame);
    d->view->setAttribute(Qt::WA_MacShowFocusRect, false);
    d->view->setColumnWidths(QList<int>() << 200 << 200 << 200);
    d->view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    d->view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    d->view->setModel(d->model);
    d->view->setRootIndex(d->model->index(dtkScriptManager::instance()->scriptPath()));
    d->view->setPreviewWidget(d->description);

    connect(d->view, SIGNAL(clicked(const QModelIndex&)), this, SLOT(onModelIndexClicked(const QModelIndex&)));
    connect(d->view, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(onModelIndexDoubleClicked(const QModelIndex&)));
    connect(d->view, SIGNAL(updatePreviewWidget(const QModelIndex&)), this, SLOT(onModelIndexClicked(const QModelIndex&)));

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(d->view);
}

dtkCreatorScriptList::~dtkCreatorScriptList(void)
{
    delete d->description;
    delete d->view;
    delete d;

    d = NULL;
}

void dtkCreatorScriptList::onModelIndexClicked(const QModelIndex& index)
{
    d->description->setText("");

    if (d->model->fileInfo(index).isDir())
        return;
 
    QString fileName = d->model->fileInfo(index).absoluteFilePath();
   
    dtkScriptInterpreter *interpreter; int stat;
    if (fileName.endsWith(".py"))
        interpreter = dtkScriptInterpreterPool::instance()->python();
    else if (fileName.endsWith(".tcl"))
        interpreter = dtkScriptInterpreterPool::instance()->tcl();
    else
        return;

    interpreter->load(fileName);
    d->description->setText(interpreter->interpret("description", QStringList(), &stat));
    interpreter->release();    
}

void dtkCreatorScriptList::onModelIndexDoubleClicked(const QModelIndex& index)
{
    if (d->model->fileInfo(index).isDir())
        return;
 
    QString fileName = d->model->fileInfo(index).absoluteFilePath();
   
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

    connect(dtkCreatorWidgetFactory::instance(), SIGNAL(interpret(const QString&, int *)),
            interpreter,                           SLOT(interpret(const QString&, int *)));

    emit scriptClicked(fileName);
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

QSize dtkCreatorScriptWidget::sizeHint(void) const
{
    return QSize(1, 200);
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

    connect(d->list, SIGNAL(scriptClicked(const QString&)), this, SIGNAL(scriptClicked(const QString&)));
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
