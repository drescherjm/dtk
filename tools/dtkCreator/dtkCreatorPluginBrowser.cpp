/* dtkCreatorPluginBrowser.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Aug  4 10:31:04 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Sep 22 16:35:49 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 118
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkCreatorPluginBrowser.h"

#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractDataFactory.h>
#include <dtkCore/dtkAbstractProcess.h>
#include <dtkCore/dtkAbstractProcessFactory.h>
#include <dtkCore/dtkAbstractView.h>
#include <dtkCore/dtkAbstractViewFactory.h>
#include <dtkCore/dtkPlugin.h>
#include <dtkCore/dtkPluginManager.h>

#include <dtkGui/dtkTagCloud.h>

// /////////////////////////////////////////////////////////////////
// dtkCreatorPluginListPrivate
// /////////////////////////////////////////////////////////////////

class dtkCreatorPluginListPrivate
{
public:
    dtkItemView *view;
    dtkTagCloud *cloud;
    dtkTagScope *scope;

    dtkTagController *controller;
};

// /////////////////////////////////////////////////////////////////
// dtkCreatorPluginList
// /////////////////////////////////////////////////////////////////

static QString view_stylesheet =
"body { font-size: 70%; }";

static QString cloud_stylesheet =
"body      { color: rgb(99, 99,  99); }"
"a:link    { color: rgb(18, 89, 199); text-decoration:none; }"
"a:active  { color: rgb(81, 86, 151); text-decoration:none; }"
"a:hover   { color: rgb(81, 86, 151); text-decoration:underline; }";

static QString scope_stylesheet =
"body { border-bottom: 1px solid rgb(145, 145, 145); }";

dtkCreatorPluginList::dtkCreatorPluginList(QWidget *parent) : dtkSplitter(parent, true), d(new dtkCreatorPluginListPrivate)
{
    d->scope = new dtkTagScope(this);
    d->scope->setStyleSheet(scope_stylesheet);

    d->cloud = new dtkTagCloud(this);
    d->cloud->setSortingType(dtkTagCloud::Alpha);
    d->cloud->setSortingOrder(dtkTagCloud::Asc);
    d->cloud->setFontSize(18);
    d->cloud->setFontRange(10);
    d->cloud->setStyleSheet(cloud_stylesheet);

    d->view = new dtkItemView(this);
    d->view->setStyleSheet(view_stylesheet);

    d->controller = new dtkTagController;
    d->controller->attach(d->scope);
    d->controller->attach(d->view);
    d->controller->attach(d->cloud);

    foreach(dtkPlugin *plugin, dtkPluginManager::instance()->plugins())
        d->controller->addItem(plugin->name(), plugin->description(), plugin->tags(), plugin->types());

    QWidget *items = new QWidget(this);

    QVBoxLayout *layout = new QVBoxLayout(items);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(d->scope);
    layout->addWidget(d->view);
    
    this->setOrientation(Qt::Vertical);
    this->addWidget(d->cloud);
    this->addWidget(items);
    this->setSizes(QList<int>() << static_cast<int>(parent->height()*0.2) << static_cast<int>(parent->height()*0.8));

    connect(d->view, SIGNAL(typeClicked(QString)), this, SLOT(onPluginClicked(QString)));
}

dtkCreatorPluginList::~dtkCreatorPluginList(void)
{
    delete d;

    d = NULL;
}

const QString plugin_preview_stylesheet =
"<style>"
"  body {"
"     text-color = #ccc;"
"  }"
""
"  h1, h2, h3, h4, h5, h6 {"
"    font-weight:bold;"
"    font-family:Georgia, Lucida Bright, Times New Roman, serif;"
"  }"
""
"  h1 {"
"    font-size:1.8em;"
"  }"
""
"  h2 {"
"    font-size:1.6em;"
"  }"
""
"  h3 {"
"    font-size:1.4em;"
"  }"
"</style>";

void dtkCreatorPluginList::onPluginClicked(QString type)
{
    Q_UNUSED(type);

    // QTextEdit *edit = new QTextEdit; edit->setReadOnly(true);

    // QString image = "<img src=\"image://symbol.tiff\" width=\"120\" align=\"right\"/>";

    // if(dtkAbstractData *data = dtkAbstractDataFactory::instance()->create(type)) {
    //     edit->document()->addResource(QTextDocument::ImageResource, QUrl("image://symbol.tiff"), QPixmap(":images/symbol_data.tiff"));
    //     edit->setHtml(plugin_preview_stylesheet + image*/ + data->description());
    //     delete data;
    // }

    // if(dtkAbstractProcess *process = dtkAbstractProcessFactory::instance()->create(type)) {
    //     edit->document()->addResource(QTextDocument::ImageResource, QUrl("image://symbol.tiff"), QPixmap(":images/symbol_process.tiff"));
    //     edit->setHtml(plugin_preview_stylesheet /*+ image*/ + process->description());
    //     delete process;
    // }

    // if(dtkAbstractView *view = dtkAbstractViewFactory::instance()->create(type)) {
    //     edit->document()->addResource(QTextDocument::ImageResource, QUrl("image://symbol.tiff"), QPixmap(":images/symbol_view.tiff"));
    //     edit->setHtml(plugin_preview_stylesheet /*+ image*/ + view->description());
    //     delete view;
    // }

    // emit pluginClicked(edit);
}

// /////////////////////////////////////////////////////////////////
// dtkCreatorPluginWidgetPrivate
// /////////////////////////////////////////////////////////////////

class dtkCreatorPluginWidgetPrivate
{
public:
    QStackedWidget *stack;
};

// /////////////////////////////////////////////////////////////////
// dtkCreatorPluginWidget
// /////////////////////////////////////////////////////////////////

dtkCreatorPluginWidget::dtkCreatorPluginWidget(QWidget *parent) : QWidget(parent), d(new dtkCreatorPluginWidgetPrivate)
{
    d->stack = new QStackedWidget(this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(d->stack);
}

dtkCreatorPluginWidget::~dtkCreatorPluginWidget(void)
{
    delete d;

    d = NULL;
}

QSize dtkCreatorPluginWidget::sizeHint(void) const
{
    return QSize(1, 200);
}

void dtkCreatorPluginWidget::addWidget(QWidget *widget)
{
    if(!widget)
        return;

    if(QWidget *current = d->stack->currentWidget())
        d->stack->removeWidget(current);

    d->stack->addWidget(widget);
    d->stack->setCurrentWidget(widget);
}

// /////////////////////////////////////////////////////////////////
// dtkCreatorPluginBrowserPrivate
// /////////////////////////////////////////////////////////////////

class dtkCreatorPluginBrowserPrivate
{
public:
    dtkCreatorPluginList *list;
    dtkCreatorPluginWidget *widget;
};

// /////////////////////////////////////////////////////////////////
// dtkCreatorPluginBrowser
// /////////////////////////////////////////////////////////////////

dtkCreatorPluginBrowser::dtkCreatorPluginBrowser(QWidget *parent) : dtkSplitter(parent), d(new dtkCreatorPluginBrowserPrivate)
{
    d->list = new dtkCreatorPluginList(this);
    d->widget = new dtkCreatorPluginWidget(this);
    
    this->addWidget(d->list);
    this->addWidget(d->widget);
    this->setOrientation(Qt::Vertical);

    connect(d->list, SIGNAL(pluginClicked(QWidget *)), d->widget, SLOT(addWidget(QWidget *)));
}

dtkCreatorPluginBrowser::~dtkCreatorPluginBrowser(void)
{
    delete d;

    d = NULL;
}

QSize dtkCreatorPluginBrowser::sizeHint(void) const
{
    return QSize(200, 1);
}

dtkCreatorPluginList *dtkCreatorPluginBrowser::list(void)
{
    return d->list;
}

dtkCreatorPluginWidget *dtkCreatorPluginBrowser::widget(void)
{
    return d->widget;
}

void dtkCreatorPluginBrowser::onDataSelected(dtkAbstractData *data)
{
    d->widget->addWidget(data->ui());
}

void dtkCreatorPluginBrowser::onProcessSelected(dtkAbstractProcess *process)
{
    d->widget->addWidget(process->ui());
}

void dtkCreatorPluginBrowser::onViewSelected(dtkAbstractView *view)
{
    d->widget->addWidget(view->ui());
}
