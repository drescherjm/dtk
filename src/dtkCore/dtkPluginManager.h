/* dtkPluginManager.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Aug  4 12:21:09 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Mar  3 19:02:15 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 36
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
    void loadError(const QString& errorMessage);

protected:
     dtkPluginManager(void);
    ~dtkPluginManager(void);

    void   loadPlugin(const QString& path);
    void unloadPlugin(const QString& path);

    QString path(void) const;

private:
    static dtkPluginManager *s_instance;

private:
    dtkPluginManagerPrivate *d;
};

#endif
