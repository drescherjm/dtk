/* dtkPluginManager.cpp ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Aug  4 12:20:59 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Sep  5 14:14:31 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 170
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#include "dtkAbstractData.h"
#include "dtkPluginManager.h"

#include <dtkCore/dtkPlugin.h>
#include <dtkCore/dtkLog.h>

#define DTK_VERBOSE_LOAD false

class dtkPluginManagerPrivate
{
public:
    QString path;

    QHash<QString, QPluginLoader *> loaders;
};

dtkPluginManager *dtkPluginManager::instance(void)
{
    if(!s_instance) {
        s_instance = new dtkPluginManager;

        qRegisterMetaType<dtkAbstractData>("dtkAbstractData");
    }

    return s_instance;
}

void dtkPluginManager::initialize(void)
{
    if(d->path.isNull())
        this->readSettings();

    QString paths = d->path;

#ifdef Q_WS_WIN
    QStringList pathList;
    QRegExp pathFilterRx("(([a-zA-Z]:|)[^:]+)");

    int pos = 0;

    while ((pos = pathFilterRx.indexIn(paths, pos)) != -1) {

        QString pathItem = pathFilterRx.cap(1);
        pathItem.replace( "\\" , "/" );

        if (!pathItem.isEmpty())
            pathList << pathItem;

        pos += pathFilterRx.matchedLength();
    }
#else
    QStringList pathList = paths.split(":", QString::SkipEmptyParts);
#endif

    const QString appDir = qApp->applicationDirPath();

    foreach(QString path, pathList) {

        QDir dir(appDir);

        if (dir.cd(path)) {
            dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);

            foreach (QFileInfo entry, dir.entryInfoList())
                loadPlugin(entry.absoluteFilePath());
        } else {
            dtkWarning() << "Failed to load plugins from path " << path << ". Could not cd to directory.";
        }
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
    QString defaultPath;
    QDir plugins_dir;
#ifdef Q_WS_MAC
    plugins_dir = qApp->applicationDirPath() + "/../PlugIns";
#else
    plugins_dir = qApp->applicationDirPath() + "/../plugins";
#endif

    defaultPath = plugins_dir.absolutePath();
    settings.beginGroup("plugins");

    if (!settings.contains("path")) {
        dtkDebug() << "Filling in empty path in settings with default path:" << defaultPath;
        settings.setValue("path", defaultPath);
    }

    d->path = settings.value("path", defaultPath).toString();

    settings.endGroup();

    if(d->path.isEmpty()) {
        dtkWarning() << "Your dtk config does not seem to be set correctly.";
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

dtkPlugin *dtkPluginManager::plugin(const QString& name)
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

QString dtkPluginManager::path(void) const
{
    return d->path;
}

dtkPluginManager::dtkPluginManager(void) : d(new dtkPluginManagerPrivate)
{

}

dtkPluginManager::~dtkPluginManager(void)
{
    delete d;

    d = NULL;
}

/*!
    \brief      Loads the plugin from the given filename.
                Derived classes may override to prevent certain plugins being loaded,
                or provide additional functionality. In most cases they should still
                call the base implementation (this).
    \param      path : Path to plugin file to be loaded.
*/

void dtkPluginManager::loadPlugin(const QString& path)
{
    QPluginLoader *loader = new QPluginLoader(path);

    loader->setLoadHints (QLibrary::ExportExternalSymbolsHint);

    if(!loader->load()) {
        QString error = "Unable to load - ";
        error += loader->errorString();
        if(DTK_VERBOSE_LOAD) dtkDebug() << error;
        emit loadError(error);
        delete loader;
        return;
    }

    dtkPlugin *plugin = qobject_cast<dtkPlugin *>(loader->instance());

    if(!plugin) {
        QString error = "Unable to retrieve ";
        error += path;
        if(DTK_VERBOSE_LOAD) dtkDebug() << error;
        emit loadError(error);
        return;
    }

    if(!plugin->initialize()) {
        QString error = "Unable to initialize ";
        error += plugin->name();
        error += " plugin";
        if(DTK_VERBOSE_LOAD) dtkOutput() << error;
        emit loadError(error);
        return;
    }

    d->loaders.insert(path, loader);

    if(DTK_VERBOSE_LOAD) dtkOutput() << "Loaded plugin " << plugin->name() << " from " << path;

    emit loaded(plugin->name());
}

/*!
    \brief      Unloads the plugin previously loaded from the given filename.
                Derived classes may override to prevent certain plugins being unloaded,
                or provide additional functionality. In most cases they should still
                call the base implementation (this).
    \param      path : Path to plugin file to be unloaded.
*/
void dtkPluginManager::unloadPlugin(const QString& path)
{
    dtkPlugin *plugin = qobject_cast<dtkPlugin *>(d->loaders.value(path)->instance());

    if(!plugin) {
        if(DTK_VERBOSE_LOAD) dtkDebug() << "dtkPluginManager - Unable to retrieve " << plugin->name() << " plugin";
        return;
    }

    if(!plugin->uninitialize()) {
        if(DTK_VERBOSE_LOAD) dtkOutput() << "Unable to uninitialize " << plugin->name() << " plugin";
        return;
    }

    QPluginLoader *loader = d->loaders.value(path);

    if(!loader->unload()) {
        if(DTK_VERBOSE_LOAD) dtkDebug() << "dtkPluginManager - Unable to unload plugin: " << loader->errorString();
        return;
    }

    delete loader;

    d->loaders.remove(path);

    // emit unloaded(plugin->name());
}

dtkPluginManager *dtkPluginManager::s_instance = NULL;
