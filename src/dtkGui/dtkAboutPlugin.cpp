/* dtkAboutPlugin.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008-2011 - Julien Wintz, Inria.
 * Created: Mon Sep  5 13:23:20 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Sep  5 14:10:46 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 56
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkAboutPlugin.h"

#include <dtkCore/dtkPlugin.h>
#include <dtkCore/dtkPluginManager.h>

class dtkAboutPluginPrivate
{
public:
    QTextBrowser* description;
};

dtkAboutPlugin::dtkAboutPlugin(dtkPlugin *plugin, QWidget *parent) : QWidget(parent), d(new dtkAboutPluginPrivate)
{
    this->setup(plugin);
}

dtkAboutPlugin::dtkAboutPlugin(const QString& plugin, QWidget *parent) : QWidget(parent), d(new dtkAboutPluginPrivate)
{
    this->setup(dtkPluginManager::instance()->plugin(plugin));
}

dtkAboutPlugin::~dtkAboutPlugin(void)
{
    delete d;

    d = NULL;
}

void dtkAboutPlugin::setup(dtkPlugin *plugin)
{
    if(!plugin)
        return;

    d->description = new QTextBrowser(this);
    d->description->setOpenExternalLinks(true);
    d->description->setHtml(plugin->description());

    QListWidget *authors = new QListWidget(this);
    foreach(const QString& author, plugin->authors())
        authors->addItem(author);

    QListWidget *contributors = new QListWidget(this);
    foreach(const QString& contributor, plugin->contributors())
        contributors->addItem(contributor);

    QListWidget *dependencies = new QListWidget(this);
    foreach(const QString& dependency, plugin->dependencies())
        dependencies->addItem(dependency);

    QFormLayout *layout = new QFormLayout(this);
    layout->addRow("Name", new QLabel(plugin->name(), this));
    layout->addRow("Version", new QLabel(plugin->version(), this));
    layout->addRow("Description", d->description);
    layout->addRow("Authors", authors);
    layout->addRow("Contact", new QLabel(plugin->contact(), this));
    layout->addRow("Contributors", contributors);
    layout->addRow("Dependencies", dependencies);
}

void dtkAboutPlugin::setOpenExternalLinks(bool open)
{
        d->description->setOpenExternalLinks(open);
}

bool dtkAboutPlugin::openExternalLinks()
{
    return d->description->openExternalLinks();
}
