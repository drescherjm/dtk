/* dtkPluginManager.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Oct 31 15:01:29 2008 (+0100)
 * Version: $Id$
 * Last-Updated: Sat Aug  1 19:22:08 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 26
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKPLUGINMANAGER_H
#define DTKPLUGINMANAGER_H

#include <dtkCore/dtkCoreExport.h>
#include <dtkCore/dtkGlobal.h>

class dtkAbstractPlugin;

typedef dtkAbstractPlugin *(*dtkPluginInstancer)(void);
typedef void               (*dtkPluginDestroyer)(void);

class dtkPluginManagerPrivate;

class DTKCORE_EXPORT dtkPluginManager : public QObject 
{
    Q_OBJECT

public:
    static dtkPluginManager *instance(void);
    
    bool isPlugin(QLibrary& library);
    bool isPlugin(const QString& fileName);
    
    void startPlugins(void);
    void stopPlugins(void);
    
    bool startPlugin(const QString& id);
    void stopPlugin(const QString& id);
    
    bool start(dtkAbstractPlugin *plugin);
    void stop(dtkAbstractPlugin *plugin);

          dtkAbstractPlugin *  loadPlugin (QLibrary *library);
          dtkAbstractPlugin *  loadPlugin (const QString& fileName);
    QList<dtkAbstractPlugin *> loadPlugins(const QString& dirPath);
            
          dtkAbstractPlugin *  plugin (QString id) const;
    QList<dtkAbstractPlugin *> plugins(void) const;

    void printPlugins(void);

signals:
    void initFailed(dtkAbstractPlugin *plugin);
    void stopFailed(dtkAbstractPlugin *plugin);
    
    void initing(dtkAbstractPlugin *plugin);
    void inited(dtkAbstractPlugin *plugin);
    
    void stopping(dtkAbstractPlugin *plugin);
    void stopped(dtkAbstractPlugin *plugin);
    
private:
     dtkPluginManager(QObject *parent = 0);
    ~dtkPluginManager(void);

    QStringList reverseDependences(const QString& id);
    QStringList reverseDependences(dtkAbstractPlugin *plugin);
    
    bool resolveDependences(dtkAbstractPlugin *plugin);
    
    bool canStart(dtkAbstractPlugin *plugin);
    
    bool   hasLibrary(const QString& fileName);
    QLibrary *library(const QString& fileName);

private:
    static dtkPluginManager *s_instance;

private:
    dtkPluginManagerPrivate *d;
};

#endif
