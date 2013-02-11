/* dtkCorePluginManager.h --- 
 * 
 * Author: Julien Wintz
 * Created: Mon Feb 11 12:07:50 2013 (+0100)
 * Version: 
 * Last-Updated: Mon Feb 11 15:23:46 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 29
 */

/* Change Log:
 * 
 */

#pragma once

#include <QtCore/QObject>

class dtkCorePluginManagerPrivate;

class dtkCorePluginManager : public QObject
{
    Q_OBJECT

public:
     dtkCorePluginManager(void);
    ~dtkCorePluginManager(void);

#pragma mark -
#pragma Manager Management

    virtual void   initialize(void) = 0;
    virtual void   initialize(const QString& path);
    virtual void uninitialize(void);

#pragma mark -
#pragma Plugin Management

    virtual void   scan(const QString& path);
    virtual void   load(const QString& path) = 0;
    virtual void unload(const QString& path);

#pragma mark -
#pragma Plugin Queries
    
    QStringList plugins(void);

protected:
    dtkCorePluginManagerPrivate *d;
};
