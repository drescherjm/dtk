/* dtkPluginManager.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Aug  4 12:21:09 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Oct 26 10:17:34 2009 (+0100)
 *           By: Julien Wintz
 *     Update #: 35
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

    virtual void  readSettings(void);
    virtual void writeSettings(void);

    void printPlugins(void);

          dtkPlugin *  plugin(const QString& name);
    QList<dtkPlugin *> plugins(void);

    void setPath(const QString& path);

signals:
    void   loaded(const QString& plugin);
    void unloaded(const QString& plugin);

protected:
     dtkPluginManager(void);
    ~dtkPluginManager(void);

    void   loadPlugin(const QString& path);
    void unloadPlugin(const QString& path);
    QString path()const;

private:
    static dtkPluginManager *s_instance;
    QString path()const;
private:
    dtkPluginManagerPrivate *d;
};

#endif
