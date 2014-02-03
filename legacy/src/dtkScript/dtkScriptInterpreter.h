/* dtkScriptInterpreter.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Nov 26 16:10:31 2008 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Jan 10 14:25:45 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 203
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKSCRIPTINTERPRETER_H
#define DTKSCRIPTINTERPRETER_H

#include "dtkScriptExport.h"

#include <QtCore>

// /////////////////////////////////////////////////////////////////
// dtkScriptInterpreter
// /////////////////////////////////////////////////////////////////

class dtkScriptInterpreterPrivate;

class DTKSCRIPT_EXPORT dtkScriptInterpreter : public QObject
{
    Q_OBJECT

public:
    enum Status {
        Status_Ok,
        Status_Error,
        Status_Return,
        Status_Break,
        Status_Continue
    };

public:
             dtkScriptInterpreter(QObject *parent = 0);
    virtual ~dtkScriptInterpreter(void);

public slots:
    virtual QString interpret(const QString& command, int *stat) = 0;

private:
    dtkScriptInterpreterPrivate *d;
};

#endif
