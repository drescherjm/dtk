/* dtkPluginManager.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Aug  4 12:20:59 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Jan 27 14:06:30 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 103
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkPluginManager.h"

#include <dtkCore/dtkPlugin.h>
#include <dtkCore/dtkLog.h>

class dtkPluginManagerPrivate
{
public:
    QString path;

    QHash<QString, QPluginLoader *> loaders;
};

dtkPluginManager *dtkPluginManager::instance(void)
{
    if(!s_instance)
        s_instance = new dtkPluginManager;

    return s_instance;
}

void dtkPluginManager::initialize(void)
{
    if(d->path.isNull())
        this->readSettings();

    if(d->path.isEmpty())
        return;

    foreach(QString path, d->path.split(":", QString::SkipEmptyParts)) {

        QDir dir(path);
        dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
        
        foreach (QFileInfo entry, dir.entryInfoList())
            loadPlugin(entry.absoluteFilePath());
    }
}

void dtkPluginManager::uninitialize(void)
{
    this->writeSettings();

    foreach(QString path, d->loaders.keys())
        unloadPlugin(path);
}

void dtkPluginManager::readSettings(void)
{
    QSettings settings("inria", "dtk");
    settings.beginGroup("plugins");
    d->path = settings.value("path").toString();
    settings.endGroup();

    if(d->path.isEmpty()) {
        dtkWarning() << "Your dtk confg does not seem to be set correctly.";
        dtkWarning() << "Please set plugins.path.";
    }
}

void dtkPluginManager::writeSettings(void)
{
    QSettings settings("inria", "dtk");
    settings.beginGroup("plugins");
    settings.setValue("path", d->path);
    settings.endGroup();
}

void dtkPluginManager::printPlugins(void)
{
    foreach(QString path, d->loaders.keys())
        dtkOutput() << path;
}

dtkPlugin *dtkPluginManager::plugin(QString name)
{
    foreach(QPluginLoader *loader, d->loaders) {
        dtkPlugin *plugin = qobject_cast<dtkPlugin *>(loader->instance());

        if(plugin->name() == name)
            return plugin;
    }

    return NULL;
}

QList<dtkPlugin *> dtkPluginManager::plugins(void)
{
    QList<dtkPlugin *> list;
    
    foreach(QPluginLoader *loader, d->loaders)
        list << qobject_cast<dtkPlugin *>(loader->instance());

    return list;
}

void dtkPluginManager::setPath(const QString& path)
{
    d->path = path;
}

dtkPluginManager::dtkPluginManager(void) : d(new dtkPluginManagerPrivate)
{

}

dtkPluginManager::~dtkPluginManager(void)
{
    delete d;

    d = NULL;
}

void dtkPluginManager::loadPlugin(const QString& path)
{
    QPluginLoader *loader = new QPluginLoader(path);

    if(!loader->load()) {
        dtkDebug() << "Unable to load - " << loader->errorString();
        delete loader;
        return;
    }

    dtkPlugin *plugin = qobject_cast<dtkPlugin *>(loader->instance());

    if(!plugin) {
        dtkDebug() << "Unable to retrieve" << path;
        return;
    }

    if(!plugin->initialize()) {
        dtkOutput() << "Unable to initialize" << plugin->name() << "plugin";
        return;
    }

    d->loaders.insert(path, loader);

    emit loaded(plugin->name());
}

void dtkPluginManager::unloadPlugin(const QString& path)
{
    dtkPlugin *plugin = qobject_cast<dtkPlugin *>(d->loaders.value(path)->instance());

    if(!plugin) {
        dtkDebug() << "dtkPluginManager - Unable to retrieve" << plugin->name() << "plugin";
        return;
    }

    if(!plugin->uninitialize()) {
        dtkOutput() << "Unable to uninitialize" << plugin->name() << "plugin";
        return;
    }

    QPluginLoader *loader = d->loaders.value(path);

    if(!loader->unload()) {
        dtkDebug() << "dtkPluginManager - Unable to unload plugin:" << loader->errorString();
        return;
    }

    delete loader;

    d->loaders.remove(path);

    // emit unloaded(plugin->name());
}

dtkPluginManager *dtkPluginManager::s_instance = NULL;
