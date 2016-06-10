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

template < typename T > class dtkCorePluginTuner;

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
    typedef dtkCorePluginTuner<T> *(*tunerCreator) ();

public:
    void record(const QString& key, creator func);
    void recordTuner(const QString& key, tunerCreator func);

public:
    T *create(const QString& key) const;
    dtkCorePluginTuner<T> *createTuner(const QString& key) const;

public:
    QStringList keys(void) const;

private:
    QHash<QString, creator> creators;
    QHash<QString, tunerCreator> tuner_creators;
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
