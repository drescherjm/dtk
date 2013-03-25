/* dtkCorePlugin.h --- 
 * 
 * Author: Julien Wintz
 * Created: Thu Feb 28 16:15:02 2013 (+0100)
 * Version: 
 * Last-Updated: Mon Mar 25 10:21:13 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 113
 */

/* Change Log:
 * 
 */

#pragma once

#include "dtkCorePluginManager"
#include "dtkCorePluginFactory"

// ///////////////////////////////////////////////////////////////////
// DTK_DECLARE_OBJECT
// ///////////////////////////////////////////////////////////////////

#define DTK_DECLARE_OBJECT(type)		\
    Q_DECLARE_METATYPE(type)

// ///////////////////////////////////////////////////////////////////
// DTK_DECLARE_PLUGIN
// ///////////////////////////////////////////////////////////////////

#define DTK_DECLARE_PLUGIN_INTERFACE_NAME_STRINGIFIED(type) \
    #type

#define DTK_DECLARE_PLUGIN_INTERFACE_NAME(type) \
    fr.inria.type

#define DTK_DECLARE_PLUGIN_INTERFACE(type) \
    DTK_DECLARE_PLUGIN_INTERFACE_NAME_STRINGIFIED(DTK_DECLARE_PLUGIN_INTERFACE_NAME(type))

#define DTK_DECLARE_PLUGIN(type)		\
    class type##Plugin : public QObject		\
    {						\
	Q_OBJECT				\
						\
    public:					\
	         type##Plugin(void) {}		\
	virtual ~type##Plugin(void) {}		\
						\
    public:					\
	virtual void   initialize(void) = 0;	\
	virtual void uninitialize(void) = 0;	\
    };						\
						\
    Q_DECLARE_INTERFACE(type##Plugin, DTK_DECLARE_PLUGIN_INTERFACE(type))

// ///////////////////////////////////////////////////////////////////
// DTK_DECLARE_PLUGIN_FACTORY
// ///////////////////////////////////////////////////////////////////

#define DTK_DECLARE_PLUGIN_FACTORY(type)        \
    class type##PluginFactory : public dtkCorePluginFactory<type> {};

// ///////////////////////////////////////////////////////////////////
// DTK_DECLARE_PLUGIN_MANAGER
// ///////////////////////////////////////////////////////////////////

#define DTK_DECLARE_PLUGIN_MANAGER(type)        \
    class type##PluginManager : public dtkCorePluginManager<type##Plugin> {};
