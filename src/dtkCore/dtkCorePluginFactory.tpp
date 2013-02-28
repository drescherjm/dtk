/* dtkCorePluginFactory.tpp --- 
 * 
 * Author: Julien Wintz
 * Created: Fri Feb  8 16:20:47 2013 (+0100)
 * Version: 
 * Last-Updated: 2013 Thu Feb 28 20:00:19 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 67
 */

/* Change Log:
 * 
 */

#pragma once

template <typename T> dtkCorePluginFactory<T>::dtkCorePluginFactory(void)
{
    
}

template <typename T> dtkCorePluginFactory<T>::~dtkCorePluginFactory(void)
{

}

#pragma mark -
#pragma Type creator registration

template <typename T> void dtkCorePluginFactory<T>::record(QString key, creator func)
{
    this->creators.insert(key, func);
}

#pragma mark -
#pragma Type creator invokation

template <typename T> T *dtkCorePluginFactory<T>::create(const QString& key)
{
    return this->creators.value(key)();
}

#pragma mark -
#pragma Type creator inspection

template <typename T> QStringList dtkCorePluginFactory<T>::keys(void)
{
    return this->creators.keys();
}
