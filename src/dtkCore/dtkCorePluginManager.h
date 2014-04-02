/* dtkCorePluginManager.h --- 
 * 
 * Author: Julien Wintz
 * Created: Mon Feb 11 12:07:50 2013 (+0100)
 * Version: 
 * Last-Updated: mer. avril  2 10:04:36 2014 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 53
 */

/* Change Log:
 * 
 */

#pragma once

#include <QtCore>

template <typename T> class dtkCorePluginManagerPrivate;

// ///////////////////////////////////////////////////////////////////
// dtkCorePluginManager
// ///////////////////////////////////////////////////////////////////

template <typename T> class dtkCorePluginManager : public QObject
{
public:
     dtkCorePluginManager();
    ~dtkCorePluginManager();

#pragma mark -
#pragma Manager Management

    virtual void   initialize(const QString& path);
    virtual void uninitialize();

#pragma mark -
#pragma Plugin Management

    virtual void   scan(const QString& path);
    virtual void   load(const QString& path);
    virtual void unload(const QString& path);

#pragma mark -
#pragma Plugin Queries
    
    QStringList plugins();

protected:
    dtkCorePluginManagerPrivate<T> *d;
};

// ///////////////////////////////////////////////////////////////////

#include "dtkCorePluginManager_t.h"
