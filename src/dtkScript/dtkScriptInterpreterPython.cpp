/* dtkScriptInterpreterPython.cpp --- 
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Nov 26 16:29:02 2008 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Jan 11 14:49:03 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 613
 */

/* Commentary: 
 *
 */

/* Change log:
 *
 */

#include "dtkScriptInterpreterPython.h"

#include <dtkLog/dtkLog.h>
#include <dtkLog/dtkLogger.h>

#include <QtCore>

#include <Python.h>

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

static const QString dtkScriptInterpreterPythonRedirector_declare = 
    "import sys\n"
    "\n"
    "class Redirector:\n"
    "    def __init__(self):\n"
    "        self.data = ''\n"
    "    def write(self, stuff):\n"
    "        self.data+= stuff\n";

static const QString dtkScriptInterpreterPythonRedirector_define = 
    "redirector = Redirector()\n"
    "sys.stdout = redirector\n"
    "sys.stderr = redirector\n";

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

class dtkScriptInterpreterPythonPrivate
{
public:
    QString buffer;
};

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

dtkScriptInterpreterPython::dtkScriptInterpreterPython(QObject *parent) : dtkScriptInterpreter(parent), d(new dtkScriptInterpreterPythonPrivate)
{
    Py_Initialize();
    PyRun_SimpleString(dtkScriptInterpreterPythonRedirector_declare.toAscii().constData());
}

dtkScriptInterpreterPython::~dtkScriptInterpreterPython(void)
{
    Py_Finalize();

    delete d;

    d = NULL;
}

QString dtkScriptInterpreterPython::interpret(const QString& command, int *stat)
{
    QString statement = command;

    if(command.endsWith(":")) {
        if(!d->buffer.isEmpty())
            d->buffer.append("\n");
        d->buffer.append(command);
        return "";
    }

    if(!command.isEmpty() && command.startsWith(" ")) {
        if(!d->buffer.isEmpty())
            d->buffer.append("\n");
        d->buffer.append(command);
        return "";
    }

    if(command.isEmpty() && !d->buffer.isEmpty()) {
        if(!d->buffer.isEmpty())
            d->buffer.append("\n");
        statement = d->buffer;
        d->buffer.clear();
    }

    if(statement.isEmpty())
        return "";

    PyObject *module = PyImport_AddModule("__main__");

    PyRun_SimpleString(dtkScriptInterpreterPythonRedirector_define.toAscii().constData());
    
    switch(PyRun_SimpleString(statement.toAscii().constData())) {
    case  0: *stat = Status_Ok;    break;
    case -1: *stat = Status_Error; break;
    default: break;
    }

    PyErr_Print();
    
    PyObject *redtor = PyObject_GetAttrString(module, "redirector");
    PyObject *result = PyObject_GetAttrString(redtor, "data");

    return QString(PyString_AsString(result)).simplified();
}
