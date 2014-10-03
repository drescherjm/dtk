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

#pragma mark -
#pragma mark Type creator definition

    typedef T *(*creator) ();

#pragma mark -
#pragma mark Type creator registration

    void record(const QString& key, creator func);

#pragma mark -
#pragma mark Type creator invokation

    T *create(const QString& key);

#pragma mark -
#pragma mark Type creator inspection

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
