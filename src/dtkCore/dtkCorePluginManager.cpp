/* dtkCorePluginManager.cpp --- 
 * 
 * Author: Julien Wintz
 * Created: Mon Feb 11 12:08:44 2013 (+0100)
 * Version: 
 * Last-Updated: Mon Feb 11 18:52:16 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 29
 */

/* Change Log:
 * 
 */

#include "dtkCorePluginManager.h"
#include "dtkCorePluginManager_p.h"

#include <QtCore>
#include <QtDebug>

// ///////////////////////////////////////////////////////////////////
// dtkCorePluginManagerPrivate
// ///////////////////////////////////////////////////////////////////

bool dtkCorePluginManagerPrivate::check(const QString& path)
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

dtkCorePluginManager::dtkCorePluginManager(void) : d(new dtkCorePluginManagerPrivate)
{

}

dtkCorePluginManager::~dtkCorePluginManager(void)
{
    delete d;

    d = NULL;
}

void dtkCorePluginManager::initialize(const QString& path)
{
    QDir dir(path);

    foreach(QFileInfo info, dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot))
        this->scan(info.absoluteFilePath());

    foreach(QFileInfo info, dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot))
        this->load(info.absoluteFilePath());
}

void dtkCorePluginManager::uninitialize(void)
{
    foreach(const QString &path, d->loaders.keys())
        this->unload(path);
}

void dtkCorePluginManager::scan(const QString& path)
{
    if(!QLibrary::isLibrary(path))
        return;
    
    QPluginLoader *loader = new QPluginLoader(path);

           d->names.insert(path, loader->metaData().value("MetaData").toObject().value("name").toVariant());
        d->versions.insert(path, loader->metaData().value("MetaData").toObject().value("version").toVariant());
    d->dependencies.insert(path, loader->metaData().value("MetaData").toObject().value("dependencies").toArray().toVariantList());

    delete loader;
}

QStringList dtkCorePluginManager::plugins(void)
{
    return d->loaders.keys();
}
