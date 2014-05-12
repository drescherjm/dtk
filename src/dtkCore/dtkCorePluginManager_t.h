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

#include <QtDebug>

// ///////////////////////////////////////////////////////////////////
// dtkCorePluginManagerPrivate
// ///////////////////////////////////////////////////////////////////

template <typename T> class dtkCorePluginManagerPrivate
{
public:
    bool check(const QString& path);

public:
    QHash<QString, QVariant> names;
    QHash<QString, QVariant> versions;
    QHash<QString, QVariantList> dependencies;

public:
    QHash<QString, QPluginLoader *> loaders;
};

// ///////////////////////////////////////////////////////////////////
// dtkCorePluginManagerPrivate
// ///////////////////////////////////////////////////////////////////

template <typename T> bool dtkCorePluginManagerPrivate<T>::check(const QString& path)
{
    bool status = true;

    foreach(QVariant item, this->dependencies.value(path)) {

        QVariantMap mitem = item.toMap();
        QVariant na_mitem = mitem.value("name");
        QVariant ve_mitem = mitem.value("version");
        QString key = this->names.key(na_mitem);

        if(!this->names.values().contains(na_mitem)) {
            qDebug() << Q_FUNC_INFO << "  Missing dependency:" << na_mitem.toString() << "for plugin" << path;
            status = false;
            continue;
        }

        if (this->versions.value(key) != ve_mitem) {
            qDebug() << Q_FUNC_INFO << "    Version mismatch:" << na_mitem.toString() << "version" << this->versions.value(this->names.key(na_mitem)).toString() << "but" << ve_mitem.toString() << "required for plugin" << path;
            status = false;
            continue;
        }

        if(!check(key)) {
            qDebug() << Q_FUNC_INFO << "Corrupted dependency:" << na_mitem.toString() << "for plugin" << path;
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
    // dtkMetaPluginFactory::instance()->registerFactory<T>(this);
}

template <typename T> dtkCorePluginManager<T>::~dtkCorePluginManager(void)
{
    delete d;

    d = NULL;
}

#pragma mark -
#pragma Manager Management

template <typename T> void dtkCorePluginManager<T>::initialize(const QString& path)
{
    QDir dir(path);

    foreach(QFileInfo info, dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot))
        this->scan(info.absoluteFilePath());

    foreach(QFileInfo info, dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot))
        this->load(info.absoluteFilePath());
}

template <typename T> void dtkCorePluginManager<T>::uninitialize(void)
{
    foreach(const QString &path, d->loaders.keys())
        this->unload(path);
}

#pragma mark -
#pragma Plugin Management

template <typename T> void dtkCorePluginManager<T>::scan(const QString& path)
{
    if(!QLibrary::isLibrary(path))
        return;

    QPluginLoader *loader = new QPluginLoader(path);

           d->names.insert(path, loader->metaData().value("MetaData").toObject().value("name").toVariant());
        d->versions.insert(path, loader->metaData().value("MetaData").toObject().value("version").toVariant());
    d->dependencies.insert(path, loader->metaData().value("MetaData").toObject().value("dependencies").toArray().toVariantList());

    delete loader;
}

template <typename T> void dtkCorePluginManager<T>::load(const QString& path)
{
    if(!QLibrary::isLibrary(path))
        return;

    if(!d->check(path))
        return;

    QPluginLoader *loader = new QPluginLoader(path); // should not set this as parent to avoid bad deallocation

    if(!loader)
        return;

    loader->setLoadHints(QLibrary::ExportExternalSymbolsHint);

    T *plugin = qobject_cast<T *>(loader->instance());

    if(!plugin) {
        delete loader;
        return;
    }

    plugin->initialize();

    d->loaders.insert(path, loader);
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
    }
}

#pragma mark -
#pragma Plugin Queries

template <typename T> QStringList dtkCorePluginManager<T>::plugins(void)
{
    return d->loaders.keys();
}

//
// dtkCorePluginManager_t.h ends here
