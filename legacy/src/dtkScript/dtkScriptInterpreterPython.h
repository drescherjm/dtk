/* dtkScriptInterpreterPython.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Nov 26 16:28:12 2008 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Jan 11 10:49:04 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 51
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

class dtkScriptInterpreterPythonPrivate;

class dtkScriptInterpreterPython : public dtkScriptInterpreter
{
    Q_OBJECT

public:
    DTKSCRIPT_EXPORT  dtkScriptInterpreterPython(QObject *parent = 0);
    DTKSCRIPT_EXPORT ~dtkScriptInterpreterPython(void);

public slots:
    DTKSCRIPT_EXPORT QString interpret(const QString& command, int *stat);

private:
    dtkScriptInterpreterPythonPrivate *d;
};

#endif
