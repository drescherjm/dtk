// Version: $Id$
//
//

// Commentary:
//
//

// Change Log:
//
//

// Code:

#pragma once

#include <QtCore>

template <typename T> class dtkCorePluginManagerPrivate;

// ///////////////////////////////////////////////////////////////////
// dtkCorePluginManager
// ///////////////////////////////////////////////////////////////////

template <typename T> class dtkCorePluginManager : public QObject
{
public:
     dtkCorePluginManager(void);
    ~dtkCorePluginManager(void);

#pragma mark -
#pragma mark Manager Management

    virtual void   initialize(const QString& path);
    virtual void uninitialize(void);

public:
    void setVerboseLoading(bool value);
    bool verboseLoading(void) const;
    void setAutoLoading(bool value);
    bool autoLoading(void) const;
    void loadFromName(const QString & plugin_name);

#pragma mark -
#pragma mark Plugin Management

    virtual void   scan(const QString& path);
    virtual void   load(const QString& path);
    virtual void unload(const QString& path);

#pragma mark -
#pragma mark Plugin Queries

    QStringList plugins(void);

#pragma mark -
#pragma mark MetaData Queries

    QJsonObject metaData(const QString& pluginKey);

protected:
    dtkCorePluginManagerPrivate<T> *d;
};

#include "dtkCorePluginManager.tpp"

//
// dtkCorePluginManager.h ends here
