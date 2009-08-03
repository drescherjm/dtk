/* dtkPluginManager.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Oct 31 15:06:30 2008 (+0100)
 * Version: $Id$
 * Last-Updated: Sat Aug  1 19:44:52 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 109
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkCore/dtkGlobal.h>
#include <dtkCore/dtkAbstractPlugin.h>
#include <dtkCore/dtkPluginManager.h>
#include <dtkCore/dtkLog.h>

// /////////////////////////////////////////////////////////////////
// dtkPluginManagerPrivate
// /////////////////////////////////////////////////////////////////

class dtkPluginManagerPrivate 
{
public:
    QList<dtkAbstractPlugin *> plugins;
    QList<QLibrary *> libraries;
    QStringList pluginsRunning;
};

// /////////////////////////////////////////////////////////////////
// dtkPluginManager
// /////////////////////////////////////////////////////////////////

dtkPluginManager *dtkPluginManager::instance(void)
{
    if(!s_instance)
	s_instance = new dtkPluginManager;

    return s_instance;
}

bool dtkPluginManager::isPlugin(QLibrary& library)
{
    if (library.resolve("plugin_create_instance") == NULL)
	return(false);
    
    if (library.resolve("plugin_destroy_instance") == NULL)
	return(false);
    
    return(true);
}

bool dtkPluginManager::isPlugin(const QString& fileName)
{
    if (QLibrary::isLibrary(fileName) == false)
	return(false);

    QLibrary library(fileName);

    if (library.load() == false) {
	qDebug(qPrintable(library.errorString()));
	return(false);
    }

    bool is_plugin = isPlugin(library);

    library.unload();

    return(is_plugin);
}

dtkAbstractPlugin *dtkPluginManager::loadPlugin(const QString& fileName)
{
    QLibrary *lib = library(fileName);

    if (lib == NULL) {
	lib = new QLibrary(fileName);

	if (lib->load() == false) {
	    delete lib;
	    return(NULL);
	}
    }

    return(loadPlugin(lib));
}

dtkAbstractPlugin *dtkPluginManager::loadPlugin(QLibrary *library) 
{
    if(!d->libraries.contains(library))
	d->libraries.append(library);
    
    dtkPluginInstancer plugin_instancer = (dtkPluginInstancer) library->resolve("plugin_create_instance");
    dtkAbstractPlugin *plugin = NULL;

    if (plugin_instancer == NULL)  
	goto unload_lib;

    plugin = plugin_instancer();

    if (plugin == NULL) 
	goto unload_lib;

    plugin->setRunning(false);
    plugin->setPath(library->fileName());

    d->plugins.append(plugin);

    return(plugin);

unload_lib:
    d->libraries.removeAll(library);

    library->unload();
    delete library;

    return(NULL);
}

QList<dtkAbstractPlugin *> dtkPluginManager::loadPlugins(const QString& dirPath) 
{
    QDir dir(dirPath);
    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);

    QList<dtkAbstractPlugin *> loadedPlugins;
    QStringList possibleList;

    QFileInfoList list = dir.entryInfoList();
    foreach (QFileInfo fileInfo, list) {
	if (fileInfo.isDir() == true) {
	    loadPlugins(fileInfo.absoluteFilePath());
	} else {
	    QString filePath = fileInfo.absoluteFilePath();
	    if (isPlugin(filePath) == true) {
		dtkAbstractPlugin *plugin = loadPlugin(filePath);
		if (plugin != NULL) loadedPlugins.append(plugin);
	    } else if (QLibrary::isLibrary(filePath) == true) {
		possibleList.append(filePath);
	    }
	}
    }

    int count = possibleList.size() * possibleList.size();
    for (; possibleList.size() > 0 && count >= 0; --count) {
	QString pluginPath = possibleList.takeFirst();

	if (isPlugin(pluginPath) == true) {
	    dtkAbstractPlugin *plugin = loadPlugin(pluginPath);
	    if (plugin != NULL) loadedPlugins.append(plugin);
	} else {
	    possibleList.append(pluginPath);
	}
    }

    return(loadedPlugins);
}

QList<dtkAbstractPlugin *> dtkPluginManager::plugins(void) const 
{
    return d->plugins;
}

dtkAbstractPlugin *dtkPluginManager::plugin(QString id) const 
{
    foreach (dtkAbstractPlugin *plugin, d->plugins) {
	if (plugin->id() == id)
	    return plugin;

        if (!QString::compare(plugin->name(), id, Qt::CaseInsensitive))
            return plugin;

        if (plugin->path().contains(id))
            return plugin;
    }
    
    return(NULL);
}

void dtkPluginManager::startPlugins(void) 
{
    foreach (dtkAbstractPlugin *plugin, d->plugins)
	start(plugin);
}

void dtkPluginManager::stopPlugins(void)
{
    foreach (QString id, d->pluginsRunning)
	stopPlugin(id);
}

bool dtkPluginManager::startPlugin(const QString& id)
{
    dtkAbstractPlugin *plug = plugin(id);

    if (plug != NULL)
	return(start(plug));

    return false;
}

void dtkPluginManager::stopPlugin(const QString& id)
{
    dtkAbstractPlugin *plug = plugin(id);

    if (plug != NULL) 
	stop(plug);
}

bool dtkPluginManager::start(dtkAbstractPlugin *plugin)
{
    if (!resolveDependences(plugin))
	return(false);

    if (!canStart(plugin))
	return(false);

    emit initing(plugin);

    if (!plugin->initialize()) {
	emit initFailed(plugin);
	return(false);
    }

    plugin->setRunning(true);

    emit inited(plugin);

    d->pluginsRunning.append(plugin->id());

    return true;
}

void dtkPluginManager::stop(dtkAbstractPlugin *plugin)
{
    if (!plugin->isRunning()) return;

    foreach (QString depId, plugin->dependences())
    	stopPlugin(depId);

    emit stopping(plugin);

    if (plugin->uninitialize() == false)
	emit stopFailed(plugin);

    plugin->setRunning(false);

    d->pluginsRunning.removeAll(plugin->id());

    emit stopped(plugin);
}

bool dtkPluginManager::resolveDependences(dtkAbstractPlugin *plugin)
{
    foreach (QString depId, plugin->dependences()) {
    	if (!startPlugin(depId))
    	    return(false);
    }

    return true;
}

dtkPluginManager::dtkPluginManager(QObject *parent) : QObject(parent), d(new dtkPluginManagerPrivate)
{

}

dtkPluginManager::~dtkPluginManager(void) 
{
    delete d;

    d = NULL;
}

QStringList dtkPluginManager::reverseDependences(dtkAbstractPlugin *plugin) 
{
    return reverseDependences(plugin->id());
}

QStringList dtkPluginManager::reverseDependences(const QString& id)
{
    QStringList revDep;

    foreach (dtkAbstractPlugin *plugin, d->plugins) {
    	if (plugin->dependences().contains(id))
    	    revDep.append(plugin->id());
    }

    return revDep;
}

bool dtkPluginManager::canStart(dtkAbstractPlugin *plugin)
{
    foreach (QString depId, plugin->dependences()) {
    	if (!d->pluginsRunning.contains(depId))
    	    return(false);
    }

    return true;
}

bool dtkPluginManager::hasLibrary(const QString& fileName) 
{
    return library(fileName) != NULL;
}

QLibrary *dtkPluginManager::library(const QString& fileName) 
{
    QList<QLibrary *>::const_iterator iEnd = d->libraries.constEnd();
    QList<QLibrary *>::const_iterator i = d->libraries.constBegin();

    for (; i != iEnd; ++i) {
	if ((*i)->fileName() == fileName)
	    return *i;
    }

    return(NULL);
}

void dtkPluginManager::printPlugins(void)
{
    foreach(dtkAbstractPlugin *plugin, d->plugins)
        if (plugin->isRunning())
            dtkDebug() << plugin->name() << DTK_COLOR_FG_GREEN << "started" << DTK_NOCOLOR;
        else
            dtkDebug() << plugin->name() << DTK_COLOR_FG_YELLOW << "available" << DTK_NOCOLOR;
}

dtkPluginManager *dtkPluginManager::s_instance = NULL;
