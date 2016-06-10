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

template <typename T> dtkCorePluginFactory<T>::dtkCorePluginFactory(void)
{

}

template <typename T> dtkCorePluginFactory<T>::~dtkCorePluginFactory(void)
{

}

// /////////////////////////////////////////////////////////////////
// Type creator registration
// /////////////////////////////////////////////////////////////////

template <typename T> void dtkCorePluginFactory<T>::record(const QString& key, creator func)
{
    if (this->creators.contains(key)) {
        qDebug() << Q_FUNC_INFO << "Factory already contains key" << key << ". Nothing is done";
        return;
    }

    this->creators.insert(key, func);
}

template <typename T> void dtkCorePluginFactory<T>::recordTuner(const QString& key, tunerCreator func)
{
    if (this->tuner_creators.contains(key)) {
        qDebug() << Q_FUNC_INFO << "Factory already contains key" << key << ". Nothing is done";
        return;
    }

    this->tuner_creators.insert(key, func);
}

// /////////////////////////////////////////////////////////////////
// Type creator invokation
// /////////////////////////////////////////////////////////////////

template <typename T> T *dtkCorePluginFactory<T>::create(const QString& key) const
{
    if(!this->creators.contains(key))
        return NULL;

    return this->creators.value(key)();
}

template <typename T> dtkCorePluginTuner<T> *dtkCorePluginFactory<T>::createTuner(const QString& key) const
{
    if(!this->tuner_creators.contains(key))
        return NULL;

    return this->tuner_creators.value(key)();
}

// /////////////////////////////////////////////////////////////////
// Type creator inspection
// /////////////////////////////////////////////////////////////////

template <typename T> QStringList dtkCorePluginFactory<T>::keys(void) const
{
    return this->creators.keys();
}

//
// dtkCorePluginFactory_t.h ends here
