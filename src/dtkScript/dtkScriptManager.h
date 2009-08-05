/* dtkScriptManager.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Aug  4 21:01:13 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Aug  4 22:02:31 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 12
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKSCRIPTMANAGER_H
#define DTKSCRIPTMANAGER_H

#include <QtCore>

#include "dtkScriptExport.h"

class dtkScriptInterpreter;
class dtkScriptManagerPrivate;

class DTKSCRIPT_EXPORT dtkScriptManager : public QObject
{
    Q_OBJECT

public:
    static dtkScriptManager *instance(void);

    void   initialize(void);
    void uninitialize(void);

    void  readSettings(void);
    void writeSettings(void);

    dtkScriptInterpreter *  loadScript(const QString& path);
    dtkScriptInterpreter *unloadScript(const QString& path);
    dtkScriptInterpreter *reloadScript(const QString& path);

    QString scriptPath(void) const;
    QString modulePath(void) const;

protected:
     dtkScriptManager(void);
    ~dtkScriptManager(void);

private:
    static dtkScriptManager *s_instance;

private:
    dtkScriptManagerPrivate *d;
};

#endif
