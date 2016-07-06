// Version: $Id$
//
//

// Commentary:
//
//

// Change Log:
//
//

// Code:

#pragma once

#include "dtkCorePluginManagerBase.h"
#include "dtkCore.h"

#include <dtkLog>


// ///////////////////////////////////////////////////////////////////
// dtkCorePluginManagerPrivate
// ///////////////////////////////////////////////////////////////////

template <typename T> class dtkCorePluginManagerPrivate
{
public:
    bool check(const QString& path, bool checkConcept = true);

public:
    bool verboseLoading;
    bool autoLoading;
    QString layerVersion = QString();

public:
    QHash<QString, QVariant> pluginsLayerVersion;
    QHash<QString, QVariantList> dependencies;

public:
    QHash<QString, QPluginLoader *> loaders;

};

// ///////////////////////////////////////////////////////////////////
// dtkCorePluginManagerPrivate
// ///////////////////////////////////////////////////////////////////

template <typename T> bool dtkCorePluginManagerPrivate<T>::check(const QString& path, bool checkConcept)
{
    bool status = true;

    if (checkConcept) {
        QString conceptName = QMetaType::typeName(qMetaTypeId<T*>());
        conceptName.remove("Plugin*");

        QString pluginConcept = dtkCorePluginManagerBase::instance()->concept(path).toString();

        if (conceptName != pluginConcept) {
            if (this->verboseLoading) {
                dtkTrace() << "skip plugin: not an implementation of the current concept" << conceptName << ", current is " << pluginConcept;
            }
            return false;
        }
    }


    if (!layerVersion.isNull() && !checkVersion(layerVersion ,this->pluginsLayerVersion.value(path).toString())) {
        dtkWarn() << "    Version mismatch: layer version " << layerVersion
                  << " plugin compiled for layer version" << this->pluginsLayerVersion.value(path).toString()
                  << " for plugin " << path;
        return false;
    }

    foreach(QVariant item, this->dependencies.value(path)) {

        QVariantMap mitem = item.toMap();
        QVariant na_mitem = mitem.value("name");
        QVariant ve_mitem = mitem.value("version");
        QString key = dtkCorePluginManagerBase::instance()->pluginPath(na_mitem);

        if(!dtkCorePluginManagerBase::instance()->hasName(na_mitem)) {
            dtkWarn() << "  Missing dependency:" << na_mitem.toString() << "for plugin" << path;
            status = false;

            continue;
        }

        if (checkVersion(ve_mitem.toString(), dtkCorePluginManagerBase::instance()->version(key).toString())) {
            dtkWarn() << "    Version mismatch:" << na_mitem.toString() << "version" << dtkCorePluginManagerBase::instance()->version(key).toString() << "but" << ve_mitem.toString() << "required for plugin" << path;

            status = false;

            continue;
        }

        if(!check(key, false)) {
            dtkWarn() << "Corrupted dependency:" << na_mitem.toString() << "for plugin" << path;

            status = false;

            continue;
        }
    }

    return status;
}

// ///////////////////////////////////////////////////////////////////
// dtkCorePluginManager
// ///////////////////////////////////////////////////////////////////

template <typename T> dtkCorePluginManager<T>::dtkCorePluginManager(void) : d(new dtkCorePluginManagerPrivate<T>)
{
    d->verboseLoading = false;
    d->autoLoading = true;
}

template <typename T> dtkCorePluginManager<T>::~dtkCorePluginManager(void)
{
    delete d;

    d = NULL;
}

// /////////////////////////////////////////////////////////////////
// Logging
// /////////////////////////////////////////////////////////////////

template <typename T> void dtkCorePluginManager<T>::setVerboseLoading(bool value)
{
    d->verboseLoading = value;
}

template <typename T> bool dtkCorePluginManager<T>::verboseLoading(void) const
{
    return d->verboseLoading;
}

// /////////////////////////////////////////////////////////////////
// Auto loading
// /////////////////////////////////////////////////////////////////

template <typename T> void dtkCorePluginManager<T>::setAutoLoading(bool value)
{
    d->autoLoading = value;
}

template <typename T> bool dtkCorePluginManager<T>::autoLoading(void) const
{
    return d->autoLoading;
}

template <typename T> void dtkCorePluginManager<T>::loadFromName(const QString & plugin_name)
{
    QString full_name = plugin_name % "Plugin";

    auto i = dtkCorePluginManagerBase::instance()->namesBegin();
    auto e = dtkCorePluginManagerBase::instance()->namesEnd();

    while (i != e) {
        if(QString::compare(i.value().toString(), full_name) == 0) {
            this->load(i.key());
            return;
        }
        ++i;
    }

    dtkWarn() << Q_FUNC_INFO << plugin_name << " not found ";
    dtkWarn() << Q_FUNC_INFO << "keys" << dtkCorePluginManagerBase::instance()->pluginPaths() << dtkCorePluginManagerBase::instance()->names();
}

// /////////////////////////////////////////////////////////////////
// set Layer Version
// /////////////////////////////////////////////////////////////////

template <typename T>  void dtkCorePluginManager<T>::setLayerVersion(QString layer_version)
{
    d->layerVersion = layer_version;
}

// /////////////////////////////////////////////////////////////////
// Manager Management
// /////////////////////////////////////////////////////////////////

template <typename T> void dtkCorePluginManager<T>::initialize(const QString& path)
{

    foreach(QString path2, path.split(":", QString::SkipEmptyParts)) {

        QDir dir(path2);

        if (d->verboseLoading) {
            dtkTrace() << "scanning directory for plugins:" << path2;
        }

        foreach(QFileInfo info, dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot))
            this->scan(info.absoluteFilePath());

        if(d->autoLoading) {
            foreach(QFileInfo info, dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot))
                this->load(info.absoluteFilePath());
        }
    }
}

template <typename T> void dtkCorePluginManager<T>::uninitialize(void)
{
    foreach(const QString &path, d->loaders.keys())
        this->unload(path);
}

// /////////////////////////////////////////////////////////////////
// Plugin Management
// /////////////////////////////////////////////////////////////////

template <typename T> void dtkCorePluginManager<T>::scan(const QString& path)
{
    if(!QLibrary::isLibrary(path))
        return;

    QPluginLoader *loader = new QPluginLoader(path);

    dtkCorePluginManagerBase::instance()->insertName(path, loader->metaData().value("MetaData").toObject().value("name").toVariant());
    dtkCorePluginManagerBase::instance()->insertVersion(path, loader->metaData().value("MetaData").toObject().value("version").toVariant());
    dtkCorePluginManagerBase::instance()->insertConcept(path, loader->metaData().value("MetaData").toObject().value("concept").toVariant());
    d->dependencies.insert(path, loader->metaData().value("MetaData").toObject().value("dependencies").toArray().toVariantList());
    d->pluginsLayerVersion.insert(path, loader->metaData().value("MetaData").toObject().value("layerVersion").toVariant());

    delete loader;
}

template <typename T> void dtkCorePluginManager<T>::load(const QString& path)
{
    if(!QLibrary::isLibrary(path)) {
        QString error = "Unable to load non library file " + path;
        if(d->verboseLoading) { dtkWarn() << error; }
        return;
    }

    if(!d->check(path)) {
        QString error = "check failure for plugin file " + path;
        if(d->verboseLoading) { dtkWarn() << error; }
        return;
    }

    QPluginLoader *loader = new QPluginLoader(path); // should not set this as parent to avoid bad deallocation

    if(!loader) {
        QString error = "Empty loader for file " + path;
        if(d->verboseLoading) { dtkWarn() << error; }
        return;
    }

    loader->setLoadHints(QLibrary::ExportExternalSymbolsHint);

    if (d->verboseLoading) {
        dtkTrace() << "Loading plugin from " << path;
    }

    if(!loader->load()) {
        QString error = "Unable to load ";
        error += path;
        error += " - ";
        error += loader->errorString();
        dtkWarn() << error;
        delete loader;
        return;
    }

    T *plugin = qobject_cast<T *>(loader->instance());

    if (!plugin) {
        QString error = "Unable to retrieve ";
        error += path;
        dtkWarn() << error;

        loader->unload();
        delete loader;
        return;
    }

    plugin->initialize();

    d->loaders.insert(path, loader);

    if (d->verboseLoading) {
        QString name =  loader->metaData().value("MetaData").toObject().value("name").toString();
        dtkTrace() << "Loaded plugin " <<  name  << " from " << path;
    }
}

template <typename T> void dtkCorePluginManager<T>::unload(const QString& path)
{
    QPluginLoader *loader = d->loaders.value(path);

    T *plugin = qobject_cast<T *>(loader->instance());

    if (plugin)
        plugin->uninitialize();

    if(loader->unload()) {
        d->loaders.remove(path);
        delete loader;
    } else {
        dtkWarn() << Q_FUNC_INFO << loader->errorString();
    }
}

// /////////////////////////////////////////////////////////////////
// Plugin Queries
// /////////////////////////////////////////////////////////////////

template <typename T> QStringList dtkCorePluginManager<T>::plugins(void)
{
    return d->loaders.keys();
}

// /////////////////////////////////////////////////////////////////
// metaData Queries
// /////////////////////////////////////////////////////////////////

template <typename T> QJsonObject dtkCorePluginManager<T>::metaData(const QString& pluginKey)
{
    if(d->loaders.keys().contains(pluginKey))
        return d->loaders[pluginKey]->metaData();
    return QJsonObject();
}

//
// dtkCorePluginManager_t.h ends here
