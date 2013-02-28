/* dtkCorePluginFactory.h --- 
 * 
 * Author: Thibaud Kloczko
 * Created: 2013 Thu Feb 28 14:13:28 (+0100)
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#pragma once

#include <QtCore>

//template <typename T> class dtkCorePluginFactoryPrivate;

template <typename T> class dtkCorePluginFactory : public QObject
{
public:
    typedef T *(*creator) (void);

public:
     dtkCorePluginFactory(void);
    ~dtkCorePluginFactory(void);

public:
    T *create(const QString& key);

public:
    QStringList keys(void);

public:
    void record(QString key, creator func);

private:
    QHash<QString, creator> creators;
    //dtkCorePluginFactoryPrivate<T> *d;
};

#include "dtkCorePluginFactory.tpp"
