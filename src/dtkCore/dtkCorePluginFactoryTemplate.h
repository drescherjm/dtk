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

#include <typeinfo>

// ///////////////////////////////////////////////////////////////////
// dtkCorePluginFactoryTemplate
// ///////////////////////////////////////////////////////////////////

class dtkCorePluginFactoryTemplate : public QObject
{
public:
     dtkCorePluginFactoryTemplate(void) : QObject() {;}
    ~dtkCorePluginFactoryTemplate(void) {;}

public:
    template <typename FactoryType> FactoryType *pluginFactory(void);

private:
    QMap<QString, void *> m_factories;
};

// ///////////////////////////////////////////////////////////////////

template <typename FactoryType> inline FactoryType *dtkCorePluginFactoryTemplate::pluginFactory(void)
{
    QString factoryTypeName = QString(typeid(FactoryType).name());

    if (!m_factories.contains(factoryTypeName)) {
        FactoryType *factory = new FactoryType;
        m_factories.insert(factoryTypeName, factory);
    }
    
    return static_cast<FactoryType *>(m_factories[factoryTypeName]);
}

// 
// dtkCorePluginFactoryTemplate.h ends here
