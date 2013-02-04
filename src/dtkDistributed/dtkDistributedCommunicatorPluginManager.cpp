/* dtkDistributedCommunicatorPluginManager.cpp --- 
 * 
 * Author: Julien Wintz
 * Created: Mon Feb  4 12:51:32 2013 (+0100)
 * Version: 
 * Last-Updated: Mon Feb  4 12:52:09 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 2
 */

/* Change Log:
 * 
 */

#include "dtkDistributedCommunicatorPlugin.h"
#include "dtkDistributedCommunicatorPluginManager.h"

#include <QtCore>
#include <QtDebug>

// /////////////////////////////////////////////////////////////////
// dtkDistributedCommunicatorPluginManagerPrivate
// /////////////////////////////////////////////////////////////////

class dtkDistributedCommunicatorPluginManagerPrivate
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

bool dtkDistributedCommunicatorPluginManagerPrivate::check(const QString& path)
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

// /////////////////////////////////////////////////////////////////
// dtkDistributedCommunicatorPluginManager
// /////////////////////////////////////////////////////////////////

dtkDistributedCommunicatorPluginManager *dtkDistributedCommunicatorPluginManager::instance(void)
{
    if(!s_instance)
        s_instance = new dtkDistributedCommunicatorPluginManager;

    return s_instance;
}

void dtkDistributedCommunicatorPluginManager::initialize(void)
{
    QDir path = QDir(qApp->applicationDirPath());
    path.cdUp();
    path.cd("plugins");

    foreach(QFileInfo info, path.entryInfoList(QDir::Files | QDir::NoDotAndDotDot))
        this->scan(info.absoluteFilePath());

    foreach(QFileInfo info, path.entryInfoList(QDir::Files | QDir::NoDotAndDotDot))
        this->load(info.absoluteFilePath());
}

void dtkDistributedCommunicatorPluginManager::uninitialize(void)
{
    foreach(const QString &path, d->loaders.keys())
        this->unload(path);
}

void dtkDistributedCommunicatorPluginManager::scan(const QString& path)
{
    if(!QLibrary::isLibrary(path))
        return;
    
    QPluginLoader *loader = new QPluginLoader(path);

           d->names.insert(path, loader->metaData().value("MetaData").toObject().value("name").toVariant());
        d->versions.insert(path, loader->metaData().value("MetaData").toObject().value("version").toVariant());
    d->dependencies.insert(path, loader->metaData().value("MetaData").toObject().value("dependencies").toArray().toVariantList());

    delete loader;
}

void dtkDistributedCommunicatorPluginManager::load(const QString& path)
{
    if(!QLibrary::isLibrary(path))
        return;

    if(!d->check(path))
        return;

    QPluginLoader *loader = new QPluginLoader(path);

    if(dtkDistributedCommunicatorPlugin *plugin = qobject_cast<dtkDistributedCommunicatorPlugin *>(loader->instance()))
        d->loaders.insert(path, loader);
    else
        delete loader;
}

void dtkDistributedCommunicatorPluginManager::unload(const QString& path)
{
    QPluginLoader *loader = d->loaders.value(path);

    if(loader->unload()) {
        d->loaders.remove(path);
        delete loader;
    }
}

QStringList dtkDistributedCommunicatorPluginManager::plugins(void)
{
    return d->loaders.keys();
}

dtkDistributedCommunicatorPluginManager::dtkDistributedCommunicatorPluginManager(void) : d(new dtkDistributedCommunicatorPluginManagerPrivate)
{

}

dtkDistributedCommunicatorPluginManager::~dtkDistributedCommunicatorPluginManager(void)
{
    delete d;

    d = NULL;
}

dtkDistributedCommunicatorPluginManager *dtkDistributedCommunicatorPluginManager::s_instance = NULL;
