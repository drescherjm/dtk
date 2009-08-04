/* dtkScriptManager.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Aug  4 21:03:39 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Aug  4 21:34:52 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 28
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkScriptManager.h"

#include <dtkCore/dtkLog.h>

#include <dtkScript/dtkScriptInterpreter.h>
#include <dtkScript/dtkScriptInterpreterPython.h>
#include <dtkScript/dtkScriptInterpreterTcl.h>

class dtkScriptManagerPrivate
{
public:
    QString path;

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
    d->path = settings.value("path").toString();
    settings.endGroup();
}

void dtkScriptManager::writeSettings(void)
{
    QSettings settings("inria", "dtk");
    settings.beginGroup("scripts");
    settings.setValue("path", d->path);
    settings.endGroup();
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
    dtkScriptInterpreter *interpreter;

    if(path.endsWith("py")) 
        interpreter = new dtkScriptInterpreterPython;

    if(path.endsWith("tcl")) 
        interpreter = new dtkScriptInterpreterTcl;

    interpreter->load(path);

    d->loaders.insert(path, interpreter);

    return interpreter;
}

dtkScriptInterpreter *dtkScriptManager::unloadScript(const QString& path)
{
    dtkScriptInterpreter *interpreter = d->loaders.value(path);

    d->loaders.remove(path);

    return interpreter;
}

dtkScriptInterpreter *dtkScriptManager::reloadScript(const QString& path)
{
    this->unloadScript(path);

    return this->loadScript(path);
}

dtkScriptManager *dtkScriptManager::s_instance = NULL;
