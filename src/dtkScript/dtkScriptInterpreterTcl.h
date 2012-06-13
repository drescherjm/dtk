/* dtkScriptInterpreterTcl.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Nov 26 16:18:42 2008 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Aug  2 11:12:09 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 104
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKSCRIPTINTERPRETERTCL_H
#define DTKSCRIPTINTERPRETERTCL_H

#include <dtkCore/dtkGlobal.h>

#include "dtkScriptInterpreter.h"

struct Tcl_Interp;

// /////////////////////////////////////////////////////////////////
// dtkScriptInterpreterTcl
// /////////////////////////////////////////////////////////////////

class dtkScriptInterpreterTclPrivate;

class DTKSCRIPT_EXPORT dtkScriptInterpreterTcl : public dtkScriptInterpreter
{
    Q_OBJECT

public:
     dtkScriptInterpreterTcl(QObject *parent = 0);
    ~dtkScriptInterpreterTcl(void);

    virtual void registerVariable(bool   &var, QString name, QString description = "");
    virtual void registerVariable(int    &var, QString name, QString description = "");
    virtual void registerVariable(double &var, QString name, QString description = "");
    virtual void registerVariable(char * &var, QString name, QString description = "");

    virtual void unregisterVariable(QString name);

    Tcl_Interp *interpreter(void);

public slots:
    virtual QString interpret(const QString& command, int *stat);
    virtual QString interpret(const QString& command, const QStringList& args, int *stat);

protected:
    static char *prompt(void);

private:
    dtkScriptInterpreterTclPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkScriptInterpreterTclModuleManager
// /////////////////////////////////////////////////////////////////

class DTKSCRIPT_EXPORT dtkScriptInterpreterTclModuleManager : public QObject
{
    typedef int (*dtkScriptInterpreterModuleInitializer)(Tcl_Interp *);

public:
    static dtkScriptInterpreterTclModuleManager* instance(void) {
	if(!m_instance)
	    m_instance = new dtkScriptInterpreterTclModuleManager;

	return m_instance;
    }

    void initialize(dtkScriptInterpreterTcl *interpreter) {
	int stat;

	foreach(dtkScriptInterpreterModuleInitializer initializer, initializers)
	    initializer(interpreter->interpreter());

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
     dtkScriptInterpreterTclModuleManager(void) {}
    ~dtkScriptInterpreterTclModuleManager(void) {}

private:
    QList<dtkScriptInterpreterModuleInitializer> initializers;
    QList<QString> commands;

    static dtkScriptInterpreterTclModuleManager *m_instance;
};

#endif
