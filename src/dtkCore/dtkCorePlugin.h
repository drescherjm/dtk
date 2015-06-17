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
// DTK_OBJECT_TEMPLATE
// ///////////////////////////////////////////////////////////////////

#define DTK_OBJECT_TEMPLATE                                                     \
    public:                                                                     \
        template <typename ThisObject>                                          \
        void qt_check_for_QOBJECT_macro(const ThisObject &_q_argument) const    \
        { int i = qYouForgotTheQ_OBJECT_Macro(this, &_q_argument); i = i + 1; } \
                                                                                \
        template <typename ThisObject>                                          \
        int qYouForgotTheQ_OBJECT_Macro(ThisObject, ThisObject) { return 0; }   \
                                                                                \
        template <typename ThisObject1, typename ThisObject2>                   \
        void qYouForgotTheQ_OBJECT_Macro(ThisObject1, ThisObject2) {}           \
                                                                                \
        virtual int qt_metacall(QMetaObject::Call, int, void **) { return 0; }

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

#define DTK_DECLARE_PLUGIN(type, Export)                       \
    class Export type##Plugin : public QObject                 \
    {                                                          \
        Q_OBJECT                                               \
                                                               \
    public:                                                    \
                 type##Plugin(void) {}                         \
        virtual ~type##Plugin(void) {}                         \
                                                               \
    public:                                                    \
        virtual void   initialize(void) = 0;                   \
        virtual void uninitialize(void) = 0;                   \
    };                                                         \
                                                               \
    Q_DECLARE_INTERFACE(type##Plugin, DTK_DECLARE_PLUGIN_INTERFACE(type))

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
// DTK_DEFINE_PLUGIN
// ///////////////////////////////////////////////////////////////////

#define DTK_DEFINE_PLUGIN(type) \
    Q_PLUGIN_METADATA(IID DTK_DECLARE_PLUGIN_INTERFACE(type))

//
// dtkCorePlugin.h ends here
