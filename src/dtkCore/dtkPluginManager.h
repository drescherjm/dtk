/* dtkPluginManager.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Aug  4 12:21:09 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Aug  4 19:24:16 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 29
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKPLUGINMANAGER_H
#define DTKPLUGINMANAGER_H

#include <QtCore>

#include "dtkCoreExport.h"

class dtkPlugin;
class dtkPluginManagerPrivate;

class DTKCORE_EXPORT dtkPluginManager : public QObject
{
    Q_OBJECT

public:
    static dtkPluginManager *instance(void);

    void   initialize(void);
    void uninitialize(void);

    void  readSettings(void);
    void writeSettings(void);

    void printPlugins(void);

    dtkPlugin *plugin(QString name);

    QList<dtkPlugin *> plugins(void);

protected:
     dtkPluginManager(void);
    ~dtkPluginManager(void);

    void   loadPlugin(const QString& path);
    void unloadPlugin(const QString& path);

private:
    static dtkPluginManager *s_instance;

private:
    dtkPluginManagerPrivate *d;
};

#endif
