/* dtkScriptInterpreterPython.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Nov 26 16:28:12 2008 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Feb 11 14:09:07 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 24
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKSCRIPTINTERPRETERPYTHON_H
#define DTKSCRIPTINTERPRETERPYTHON_H

#include <dtkCore/dtkGlobal.h>

#include "dtkScriptInterpreter.h"
#include "dtkScriptManager.h"

// /////////////////////////////////////////////////////////////////
// dtkScriptInterpreterPython
// /////////////////////////////////////////////////////////////////

class dtkScriptInterpreterPythonPrivate;

class DTKSCRIPT_EXPORT dtkScriptInterpreterPython : public dtkScriptInterpreter
{
    Q_OBJECT

public:
     dtkScriptInterpreterPython(QObject *parent = 0);
    ~dtkScriptInterpreterPython(void);

    virtual void registerVariable(bool   &var, QString name, QString description = "");
    virtual void registerVariable(int    &var, QString name, QString description = "");
    virtual void registerVariable(double &var, QString name, QString description = "");
    virtual void registerVariable(char * &var, QString name, QString description = "");

    virtual void unregisterVariable(QString name);

    void allowThreads(void);
    void blockThreads(void);

public slots:
    virtual QString interpret(const QString& command, int *stat);
    virtual QString interpret(const QString& command, const QStringList& args, int *stat);

protected:
    static char *prompt(void);

private:
    dtkScriptInterpreterPythonPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkScriptInterpreterPythonModuleManager
// /////////////////////////////////////////////////////////////////

class DTKSCRIPT_EXPORT dtkScriptInterpreterPythonModuleManager : public QObject
{
    typedef int (*dtkScriptInterpreterModuleInitializer)(void);

public:
    static dtkScriptInterpreterPythonModuleManager* instance(void) {
	if(!m_instance)
	    m_instance = new dtkScriptInterpreterPythonModuleManager;

	return m_instance;
    }

    void initialize(dtkScriptInterpreterPython *interpreter) {
	int stat;

        interpreter->blockThreads();

	foreach(dtkScriptInterpreterModuleInitializer initializer, initializers)
	    initializer();

        interpreter->allowThreads();

	foreach(QString command, commands) 
	    interpreter->interpret(command, &stat);
    }

    void registerInitializer(dtkScriptInterpreterModuleInitializer initializer) {
	initializers << initializer;
    }

    void registerCommand(QString command) {
	commands << command;
    }

protected:
     dtkScriptInterpreterPythonModuleManager(void) {}
    ~dtkScriptInterpreterPythonModuleManager(void) {}

private:
    QList<dtkScriptInterpreterModuleInitializer> initializers;
    QList<QString> commands;

    static dtkScriptInterpreterPythonModuleManager *m_instance;
};

#endif
