/* dtkCorePluginFactory.h --- 
 * 
 * Author: Julien Wintz
 * Created: Thu Feb 28 15:43:06 2013 (+0100)
 * Version: 
 * Last-Updated: Thu Feb 28 15:45:40 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 7
 */

/* Change Log:
 * 
 */

#pragma once

#include <QtCore>

template <typename T> class dtkCorePluginFactory : public QObject
{
public:
     dtkCorePluginFactory(void);
    ~dtkCorePluginFactory(void);

#pragma mark -
#pragma Type creator definition

    typedef T *(*creator) (void);

#pragma mark -
#pragma Type creator registration

    void record(QString key, creator func);

#pragma mark -
#pragma Type creator invokation

    T *create(const QString& key);

#pragma mark -
#pragma Type creator inspection

    QStringList keys(void);

private:
    QHash<QString, creator> creators;
};

#include "dtkCorePluginFactory.tpp"
