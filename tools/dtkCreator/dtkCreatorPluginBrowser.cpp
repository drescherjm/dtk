/* dtkCreatorPluginBrowser.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Aug  4 10:31:04 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Aug 31 21:15:39 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 21
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkCreatorPluginBrowser.h"

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
"body      { color: rgb(99, 99,  99); background:#ffffff; }"
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
        d->controller->addItem(plugin->name(), plugin->description(), plugin->tags());

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

    connect(d->view, SIGNAL(itemClicked(QString)), this, SLOT(onPluginClicked(QString)));
}

dtkCreatorPluginList::~dtkCreatorPluginList(void)
{
    delete d;

    d = NULL;
}

void dtkCreatorPluginList::onPluginClicked(QString name)
{
    if(dtkPlugin *plugin = dtkPluginManager::instance()->plugin(name))
        if (QWidget *ui = plugin->ui()) 
            emit pluginClicked(ui);
}

// /////////////////////////////////////////////////////////////////
// dtkCreatorPluginWidgetPrivate
// /////////////////////////////////////////////////////////////////

class dtkCreatorPluginWidgetPrivate
{
public:
};

// /////////////////////////////////////////////////////////////////
// dtkCreatorPluginWidget
// /////////////////////////////////////////////////////////////////

dtkCreatorPluginWidget::dtkCreatorPluginWidget(QWidget *parent) : QStackedWidget(parent), d(new dtkCreatorPluginWidgetPrivate)
{
    this->layout()->setContentsMargins(0, 0, 0, 0);
}

dtkCreatorPluginWidget::~dtkCreatorPluginWidget(void)
{
    delete d;

    d = NULL;
}

void dtkCreatorPluginWidget::addWidget(QWidget *widget)
{
    if(QWidget *current = this->currentWidget())
        QStackedWidget::removeWidget(current);

    QStackedWidget::addWidget(widget);
    QStackedWidget::setCurrentWidget(widget);
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
    this->setStretchFactor(0, 3);
    this->setStretchFactor(1, 1);
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
