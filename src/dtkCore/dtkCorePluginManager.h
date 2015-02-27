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

public:
    virtual void   initialize(const QString& path);
    virtual void uninitialize(void);

public:
    virtual void   scan(const QString& path);
    virtual void   load(const QString& path);
    virtual void unload(const QString& path);

public:
    QStringList plugins(void);

protected:
    dtkCorePluginManagerPrivate<T> *d;
};

#include "dtkCorePluginManager.tpp"

//
// dtkCorePluginManager.h ends here
