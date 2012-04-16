/* dtkScriptInterpreterPool.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Jan 26 09:45:37 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Aug  2 14:48:52 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 22
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKSCRIPTINTERPRETERPOOL_H
#define DTKSCRIPTINTERPRETERPOOL_H

#include <dtkCore/dtkGlobal.h>

#include "dtkScriptExport.h"

class dtkScriptInterpreter;
class dtkScriptInterpreterPoolPrivate;

class DTKSCRIPT_EXPORT dtkScriptInterpreterPool : public QObject
{
    Q_OBJECT

public:
    static dtkScriptInterpreterPool *instance(void);

    dtkScriptInterpreter *console(QString type = "");
    dtkScriptInterpreter *python(void);
    dtkScriptInterpreter *tcl(void);

private:
     dtkScriptInterpreterPool(void);
    ~dtkScriptInterpreterPool(void);

    static dtkScriptInterpreterPool *m_instance;

private:
    dtkScriptInterpreterPoolPrivate *d;
};

#endif
