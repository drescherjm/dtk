/* dtkCorePluginFactory.tpp --- 
 * 
 * Author: Julien Wintz
 * Created: Fri Feb  8 16:20:47 2013 (+0100)
 * Version: 
 * Last-Updated: 2013 Thu Feb 28 14:47:18 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 54
 */

/* Change Log:
 * 
 */

#pragma once

// template <typename X> class dtkCorePluginFactoryPrivate
// {
// public:
//     dtkCorePluginFactory<X>::creator toto;
//     QHash<QString, dtkCorePluginFactory<X>::creator> creators;
// };

template <typename T>  dtkCorePluginFactory<T>::dtkCorePluginFactory(void)
{
    
}

template <typename T>  dtkCorePluginFactory<T>::~dtkCorePluginFactory(void)
{

}

template <typename T> T *dtkCorePluginFactory<T>::create(const QString& key)
{
    Q_ASSERT(this->creators.contains(key));

    return this->creators.value(key)();
}

template <typename T> QStringList dtkCorePluginFactory<T>::keys(void)
{
    return this->creators.keys();
}

template <typename T> void dtkCorePluginFactory<T>::record(QString key, creator func)
{
    this->creators.insert(key, func);
}
