/* dtkScriptManager.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Aug  4 21:03:39 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Apr  4 08:56:41 2012 (+0200)
 *           By: tkloczko
 *     Update #: 53
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkScriptManager.h"

#include <dtkLog/dtkLog.h>

#include <dtkScript/dtkScriptInterpreter.h>
#if defined(HAVE_SWIG) && defined(HAVE_PYTHON)
#include <dtkScript/dtkScriptInterpreterPython.h>
#endif
#if defined(HAVE_SWIG) && defined(HAVE_TCL)
#include <dtkScript/dtkScriptInterpreterTcl.h>
#endif

class dtkScriptManagerPrivate
{
public:
    QString script_path;
    QString module_path;

    QHash<QString, dtkScriptInterpreter *> loaders;
};

dtkScriptManager *dtkScriptManager::instance(void)
{
    if(!s_instance)
        s_instance = new dtkScriptManager;

    return s_instance;
}

void dtkScriptManager::initialize(void)
{
    this->readSettings();
}

void dtkScriptManager::uninitialize(void)
{
    this->writeSettings();
}

void dtkScriptManager::readSettings(void)
{
    QSettings settings("inria", "dtk");
    settings.beginGroup("scripts");
    d->script_path = settings.value("script_path", "/usr/local/inria/scripts").toString();
    d->module_path = settings.value("module_path", "/usr/local/inria/modules").toString();
    settings.endGroup();

    if(d->module_path.isEmpty() && d->script_path.isEmpty()) {
        dtkWarn() << "Your dtk config does not seem to be set correctly.";
        dtkWarn() << "Please set scripts.script_path.";
        dtkWarn() << "Please set scripts.module_path.";
    }
}

void dtkScriptManager::writeSettings(void)
{
    QSettings settings("inria", "dtk");
    settings.beginGroup("scripts");
    settings.setValue("script_path", d->script_path);
    settings.setValue("module_path", d->module_path);
    settings.endGroup();
}

QString dtkScriptManager::scriptPath(void) const
{
    return d->script_path;
}

QString dtkScriptManager::modulePath(void) const
{
    return d->module_path;
}

dtkScriptManager::dtkScriptManager(void) : d(new dtkScriptManagerPrivate)
{

}

dtkScriptManager::~dtkScriptManager(void)
{
    delete d;

    d = NULL;
}

dtkScriptInterpreter *dtkScriptManager::loadScript(const QString& path)
{
    DTK_UNUSED(path);

#if defined(HAVE_SWIG) && defined(HAVE_TCL) && defined(HAVE_PYTHON)
    dtkScriptInterpreter *interpreter;

    if(path.endsWith("py")) 
        interpreter = new dtkScriptInterpreterPython;

    if(path.endsWith("tcl")) 
        interpreter = new dtkScriptInterpreterTcl;

    interpreter->load(path);

    d->loaders.insert(path, interpreter);

    return interpreter;
#else
    return NULL;
#endif
}

dtkScriptInterpreter *dtkScriptManager::unloadScript(const QString& path)
{
    DTK_UNUSED(path);

#if defined(HAVE_SWIG) && defined(HAVE_TCL) && defined(HAVE_PYTHON)
    dtkScriptInterpreter *interpreter = d->loaders.value(path);

    d->loaders.remove(path);

    return interpreter;
#else
    return NULL;
#endif
}

dtkScriptInterpreter *dtkScriptManager::reloadScript(const QString& path)
{
    DTK_UNUSED(path);

#if defined(HAVE_SWIG) && defined(HAVE_TCL) && defined(HAVE_PYTHON)
    this->unloadScript(path);

    return this->loadScript(path);
#else
    return NULL;
#endif
}

dtkScriptManager *dtkScriptManager::s_instance = NULL;
