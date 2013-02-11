/* dtkCorePluginManager_p.h --- 
 * 
 * Author: Julien Wintz
 * Created: Mon Feb 11 12:13:49 2013 (+0100)
 * Version: 
 * Last-Updated: Mon Feb 11 12:44:57 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 3
 */

/* Change Log:
 * 
 */

#pragma once

#include <QtCore>
#include <QtDebug>

class dtkCorePluginManagerPrivate
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
