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

#include <QString>

#include "dtkComposerNodeLeaf.h"

template <typename T> class dtkCorePluginFactory;

// ///////////////////////////////////////////////////////////////////
// dtkComposerNodeObject definition
// ///////////////////////////////////////////////////////////////////

template <typename T> class dtkComposerNodeObject : public dtkComposerNodeLeafObject
{
public:
             dtkComposerNodeObject(void);
    virtual ~dtkComposerNodeObject(void);

public:
    void setFactory(const dtkCorePluginFactory<T>& factory);

public:
    bool createObject(const QString& implementation);

public:
    T *object(void) const;

public:
    QStringList implementations(void) const;

    QString currentImplementation(void) const;

    bool implementationHasChanged(const QString& implementation) const;

protected:
    QString m_implementation;
    T *m_object;
    const dtkCorePluginFactory<T> *m_factory;
};

// ///////////////////////////////////////////////////////////////////

#include "dtkComposerNodeObject.tpp"

// 
// dtkComposerNodeObject.h ends here
