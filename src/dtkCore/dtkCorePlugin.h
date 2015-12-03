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
#include "dtkCoreWidgetFactory.h"
#include "dtkCoreExport.h"

// ///////////////////////////////////////////////////////////////////
// DTK_DECLARE_OBJECT
// ///////////////////////////////////////////////////////////////////

#define DTK_DECLARE_OBJECT(type)                \
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

#define DTK_DECLARE_PLUGIN_MANAGER(type,Export)                              \
    class Export type##PluginManager : public dtkCorePluginManager<type##Plugin> {};

// ///////////////////////////////////////////////////////////////////
// DTK_DECLARE_WIDGET_FACTORY
// ///////////////////////////////////////////////////////////////////

#define DTK_DECLARE_WIDGET_FACTORY(type,Export)                              \
    class Export type##WidgetFactory : public dtkCoreWidgetFactory{}; \
    template <typename T> QWidget *type##WidgetCreator() { return new T; };

// ///////////////////////////////////////////////////////////////////
// DTK_DEFINE_PLUGIN
// ///////////////////////////////////////////////////////////////////

#define DTK_DEFINE_PLUGIN(type) \
    Q_PLUGIN_METADATA(IID DTK_DECLARE_PLUGIN_INTERFACE(type))

//
// dtkCorePlugin.h ends here
