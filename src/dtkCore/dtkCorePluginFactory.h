/* dtkCorePluginFactory.h --- 
 * 
 * Author: Julien Wintz
 * Created: Thu Feb 28 15:43:06 2013 (+0100)
 * Version: 
 * Last-Updated: Tue Apr  9 13:08:29 2013 (+0200)
 *           By: Julien Wintz
 *     Update #: 22
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
     dtkCorePluginFactory(void);
    ~dtkCorePluginFactory(void);

#pragma mark -
#pragma mark Type creator definition

    typedef T *(*creator) (void);

#pragma mark -
#pragma mark Type creator registration

    void record(QString key, creator func);

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

template <typename S, typename T> S *dtkCorePluginFactoryCeator(void) {
    return new T;
}

#include "dtkCorePluginFactory.tpp"
