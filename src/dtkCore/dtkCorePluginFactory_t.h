/* dtkCorePluginFactory.tpp --- 
 * 
 * Author: Julien Wintz
 * Created: Fri Feb  8 16:20:47 2013 (+0100)
 */

#pragma once

template <typename T> dtkCorePluginFactory<T>::dtkCorePluginFactory(void)
{
    
}

template <typename T> dtkCorePluginFactory<T>::~dtkCorePluginFactory(void)
{

}

#pragma mark -
#pragma mark Type creator registration

template <typename T> void dtkCorePluginFactory<T>::record(const QString& key, creator func)
{
    if (this->creators.contains(key)) {
	qDebug() << "Factory already contains key" << key << ". Nothing is done";
	return;
    }

    this->creators.insert(key, func);
}

#pragma mark -
#pragma mark Type creator invokation

template <typename T> T *dtkCorePluginFactory<T>::create(const QString& key)
{
    if(!this->creators.contains(key))
	return NULL;

    return this->creators.value(key)();
}

#pragma mark -
#pragma mark Type creator inspection

template <typename T> QStringList dtkCorePluginFactory<T>::keys(void)
{
    return this->creators.keys();
}

