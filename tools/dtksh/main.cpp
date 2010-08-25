/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Dec 10 14:05:44 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Aug 23 20:43:05 2010 (+0200)
 *           By: jwintz
 *     Update #: 18
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtGui>

#include <dtkCore/dtkPluginManager.h>

#include <dtkScript/dtkScriptInterpreter.h>
#include <dtkScript/dtkScriptInterpreterPool.h>
#include <dtkScript/dtkScriptInterpreterPython.h>
#include <dtkScript/dtkScriptInterpreterTcl.h>

#if defined(HAVE_SWIG) && defined(HAVE_PYTHON)
extern "C" int init_core(void);               // -- Initialization core layer python wrapped functions
#endif

#if defined(HAVE_SWIG) && defined(HAVE_TCL)
extern "C" int Core_Init(Tcl_Interp *interp); // -- Initialization core layer tcl    wrapped functions
#endif

int main(int argc, char **argv)
{
    QApplication application(argc, argv);
    application.setApplicationName("dtksh");
    application.setApplicationVersion("0.0.1");
    application.setOrganizationName("inria");
    application.setOrganizationDomain("fr");

    dtkPluginManager::instance()->initialize();
    dtkScriptManager::instance()->initialize();

#if defined(HAVE_SWIG) && defined(HAVE_PYTHON)
    // Setting up core python module

    dtkScriptInterpreterPythonModuleManager::instance()->registerInitializer(&init_core);
    dtkScriptInterpreterPythonModuleManager::instance()->registerCommand(
        "import core"
    );
    dtkScriptInterpreterPythonModuleManager::instance()->registerCommand(
        "dataFactory    = core.dtkAbstractDataFactory.instance()"
    );
    dtkScriptInterpreterPythonModuleManager::instance()->registerCommand(
        "processFactory = core.dtkAbstractProcessFactory.instance()"
    );
    dtkScriptInterpreterPythonModuleManager::instance()->registerCommand(
        "viewFactory    = core.dtkAbstractViewFactory.instance()"
    );
    dtkScriptInterpreterPythonModuleManager::instance()->registerCommand(
        "pluginManager  = core.dtkPluginManager.instance()"
    );
#endif

#if defined(HAVE_SWIG) && defined(HAVE_TCL)
    // Setting up core tcl module

    dtkScriptInterpreterTclModuleManager::instance()->registerInitializer(&Core_Init);
    dtkScriptInterpreterTclModuleManager::instance()->registerCommand(
        "set dataFactory    [dtkAbstractDataFactory_instance]"
    );
    dtkScriptInterpreterTclModuleManager::instance()->registerCommand(
        "set processFactory [dtkAbstractProcessFactory_instance]"
    );
    dtkScriptInterpreterTclModuleManager::instance()->registerCommand(
        "set viewFactory    [dtkAbstractViewFactory_instance]"
    );
    dtkScriptInterpreterTclModuleManager::instance()->registerCommand(
        "set pluginManager  [dtkPluginManager_instance]"
    );
#endif

    // Setting up interpreter

    dtkScriptInterpreter *interpreter = dtkScriptInterpreterPool::instance()->console("python");

    interpreter->start();

    for(int i = 1; i < argc; i++)
        interpreter->load(argv[i]);

    QObject::connect(interpreter, SIGNAL(stopped()), &application, SLOT(quit()));
    QObject::connect(&application, SIGNAL(aboutToQuit()), interpreter, SLOT(stop()));

    int status = application.exec();

    dtkScriptManager::instance()->uninitialize();
    dtkPluginManager::instance()->uninitialize();

    return status;
}
