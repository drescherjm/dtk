/* dtkCorePluginFactory.h --- 
 * 
 * Author: Julien Wintz
 * Created: Thu Feb 28 15:43:06 2013 (+0100)
 * Version: 
 * Last-Updated: mer. avril  2 10:03:47 2014 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 31
 */

/* Change Log:
 * 
 */

#pragma once

#include <QtCore>

// ///////////////////////////////////////////////////////////////////
// dtkCorePluginFactory
// ///////////////////////////////////////////////////////////////////

template <typename T> class dtkCorePluginFactory : public QObject
{
public:
     dtkCorePluginFactory();
    ~dtkCorePluginFactory();

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

    QStringList keys();

private:
    QHash<QString, creator> creators;
};

// ///////////////////////////////////////////////////////////////////
// Helper functions
// ///////////////////////////////////////////////////////////////////

template <typename S, typename T> S *dtkCorePluginFactoryCreator(void) {
    return new T;
}

#include "dtkCorePluginFactory_t.h"
