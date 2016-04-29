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

#include "dtkCorePluginManager"
#include "dtkCorePluginFactory"
#include "dtkCoreExport.h"

// ///////////////////////////////////////////////////////////////////
// DTK_DECLARE_OBJECT
// ///////////////////////////////////////////////////////////////////

#define DTK_DECLARE_OBJECT(type) \
    Q_DECLARE_METATYPE(type)

// ///////////////////////////////////////////////////////////////////
// DTK_DECLARE_PLUGIN
// ///////////////////////////////////////////////////////////////////

#define DTK_DECLARE_PLUGIN_INTERFACE_NAME_STRINGIFIED(type) \
    #type

#define DTK_DECLARE_PLUGIN_INTERFACE_NAME(type) \
    fr.inria.type

#define DTK_DECLARE_PLUGIN_INTERFACE(type)      \
    DTK_DECLARE_PLUGIN_INTERFACE_NAME_STRINGIFIED(DTK_DECLARE_PLUGIN_INTERFACE_NAME(type))

class DTKCORE_EXPORT dtkCorePluginBase : public QObject
{
    Q_OBJECT

public:
    virtual ~dtkCorePluginBase(void) {}

public:
    virtual void   initialize(void) = 0;
    virtual void uninitialize(void) = 0;
};

#define DTK_DECLARE_PLUGIN(type, Export)                                \
    class Export type##Plugin : public dtkCorePluginBase{};             \
                                                                        \
    Q_DECLARE_METATYPE(type##Plugin*);                                  \
    Q_DECLARE_INTERFACE(type##Plugin, DTK_DECLARE_PLUGIN_INTERFACE(type));

// ///////////////////////////////////////////////////////////////////
// DTK_DECLARE_PLUGIN_FACTORY
// ///////////////////////////////////////////////////////////////////

#define DTK_DECLARE_PLUGIN_FACTORY(type,Export)                              \
    class Export type##PluginFactory : public dtkCorePluginFactory<type> {}; \
    template <typename T> type *type##Creator() { return new T; };

// ///////////////////////////////////////////////////////////////////
// DTK_DECLARE_PLUGIN_MANAGER
// ///////////////////////////////////////////////////////////////////

#define DTK_DECLARE_PLUGIN_MANAGER(type,Export)                         \
    class Export type##PluginManager : public dtkCorePluginManager<type##Plugin> {};

// ///////////////////////////////////////////////////////////////////
// DTK_DEFINE_PLUGIN
// ///////////////////////////////////////////////////////////////////

#define DTK_DEFINE_PLUGIN(type) \
    Q_PLUGIN_METADATA(IID DTK_DECLARE_PLUGIN_INTERFACE(type))

// /////////////////////////////////////////////////////////////////
// DTK_DECLARE_CONCEPT
// /////////////////////////////////////////////////////////////////

#define DTK_DECLARE_CONCEPT(type, Export, Namespace)    \
    namespace Namespace                                 \
    {                                                   \
        Export type##PluginFactory& pluginFactory();    \
        Export type##PluginManager& pluginManager();    \
        Export type *create(const QString& key);        \
        Export void initialize(const QString& path);    \
        Export void uninitialize(void);                 \
    }

// /////////////////////////////////////////////////////////////////
// DTK_DEFINE_CONCEPT
// /////////////////////////////////////////////////////////////////

#define DTK_DEFINE_CONCEPT(type, Namespace)             \
    namespace Namespace                                 \
    {                                                   \
        namespace _private                              \
        {                                               \
            type##PluginFactory factory;                \
            type##PluginManager manager;                \
        }                                               \
                                                        \
        type##PluginFactory& pluginFactory()            \
        {                                               \
            return _private::factory;                   \
        }                                               \
                                                        \
        type##PluginManager& pluginManager()            \
        {                                               \
            return _private::manager;                   \
        }                                               \
                                                        \
        type *create(const QString& key)                \
        {                                               \
            return pluginFactory().create(key);         \
        }                                               \
                                                        \
        void initialize(const QString& path)            \
        {                                               \
            pluginManager().initialize(path);           \
        }                                               \
        void uninitialize(void)                         \
        {                                               \
            pluginManager().uninitialize();             \
        }                                               \
    }

//
// dtkCorePlugin.h ends here
