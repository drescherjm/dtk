/* dtkDistributedCommunicatorPluginManager.h --- 
 * 
 * Author: Julien Wintz
 * Created: Mon Feb  4 12:50:38 2013 (+0100)
 * Version: 
 * Last-Updated: Fri Feb  8 16:19:28 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 3
 */

/* Change Log:
 * 
 */

#pragma once

#include <QtCore/QObject>

class dtkDistributedCommunicatorPluginManagerPrivate;

class dtkDistributedCommunicatorPluginManager : public QObject
{
    Q_OBJECT

public:
    static dtkDistributedCommunicatorPluginManager *instance(void);

#pragma mark -
#pragma Manager Management

    void   initialize(void);
    void uninitialize(void);

#pragma mark -
#pragma Plugin Management

    void   scan(const QString& path);
    void   load(const QString& path);
    void unload(const QString& path);

#pragma mark -
#pragma Plugin Queries
    
    QStringList plugins(void);

protected:
     dtkDistributedCommunicatorPluginManager(void);
    ~dtkDistributedCommunicatorPluginManager(void);

private:
    static dtkDistributedCommunicatorPluginManager *s_instance;

 private:
    dtkDistributedCommunicatorPluginManagerPrivate *d;
};
