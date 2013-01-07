/* tstMainWindow.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Apr 10 09:19:56 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Jan  7 11:43:53 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 39
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtGui>

#include "tstMainWindow.h"

#include <dtkConfig.h>

#include <dtkScript/dtkScriptInterpreterPool.h>
#include <dtkScript/dtkScriptInterpreterPython.h>

#include <dtkGui/dtkInterpreter.h>

class tstMainWindowPrivate
{
public:
    dtkInterpreter *interpreter;

public:
    tstMainWindow *q;
};

#if defined(HAVE_SWIG) && defined(HAVE_PYTHON)
extern "C" int init_core(void);
#endif

tstMainWindow::tstMainWindow(QWidget *parent) : QMainWindow(parent)
{
    d = new tstMainWindowPrivate;

    d->interpreter = new dtkInterpreter(this);
    d->interpreter->readSettings();

    d->q = this;

    this->setWindowTitle("dtk Gui Interpreter");
    this->setCentralWidget(d->interpreter);

#if defined(HAVE_SWIG) && defined(HAVE_PYTHON)
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

    d->interpreter->registerInterpreter(dtkScriptInterpreterPool::instance()->python());
#endif
}

tstMainWindow::~tstMainWindow(void)
{
    delete d->interpreter;
    delete d;
}

dtkInterpreter *tstMainWindow::interpreter(void)
{
    return d->interpreter;
}

void tstMainWindow::closeEvent(QCloseEvent *event)
{
    d->interpreter->writeSettings();
    event->accept();
}
