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

// ///////////////////////////////////////////////////////////////////
// dtkCorePluginFactory
// ///////////////////////////////////////////////////////////////////

template <typename T> class dtkCorePluginFactory : public QObject
{
public:
     dtkCorePluginFactory(void);
    ~dtkCorePluginFactory(void);

public:
    typedef T *(*creator) ();

public:
    void record(const QString& key, creator func);

public:
    T *create(const QString& key);

public:
    QStringList keys(void);

private:
    QHash<QString, creator> creators;
};

// ///////////////////////////////////////////////////////////////////
// Helper functions
// ///////////////////////////////////////////////////////////////////

template <typename S, typename T> S *dtkCorePluginFactoryCreator(void) {
    return new T;
}

#include "dtkCorePluginFactory.tpp"

//
// dtkCorePluginFactory.h ends here
