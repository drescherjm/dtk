/* dtkScriptInterpreter.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Nov 26 16:10:31 2008 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Aug  2 11:05:12 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 176
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKSCRIPTINTERPRETER_H
#define DTKSCRIPTINTERPRETER_H

#include <dtkCore/dtkGlobal.h>

#include <dtkScript/dtkScriptExport.h>

// /////////////////////////////////////////////////////////////////
// dtkScriptInterpreterSynchronizer
// /////////////////////////////////////////////////////////////////

class DTKSCRIPT_EXPORT dtkScriptInterpreterSynchronizer
{
public:
    static dtkScriptInterpreterSynchronizer *instance(void);

    void lock(void);
    void unlock(void);
    
    void wait(void);
    void wake(void);

protected:
     dtkScriptInterpreterSynchronizer(void);
    ~dtkScriptInterpreterSynchronizer(void);

private:
    static dtkScriptInterpreterSynchronizer *m_instance;

private:
    QMutex         *mutex;
    QWaitCondition *condition;
};

// /////////////////////////////////////////////////////////////////
// dtkScriptInterpreterConsole
// /////////////////////////////////////////////////////////////////

class dtkScriptInterpreterConsolePrivate;

class DTKSCRIPT_EXPORT dtkScriptInterpreterConsole : public QThread
{
    Q_OBJECT

public:
     dtkScriptInterpreterConsole(QObject *parent);
    ~dtkScriptInterpreterConsole(void);

    void registerPrompt(char *(*prompt)(void));
    void registerBindings(QString style = "emacs");

    void run(void);

    QString prompt(void) const;

public slots:
    void start(Priority priority = InheritPriority);
    void stop(void);

    void output(const QString& result,  int *stat);

signals:
    void   input(const QString& command, int *stat);
    void    load(const QString& path);
    void    save(const QString& path);
    void    help(void);
    void stopped(void);

private:
    dtkScriptInterpreterConsolePrivate *d;
};

// /////////////////////////////////////////////////////////////////
// dtkScriptInterpreter
// /////////////////////////////////////////////////////////////////

class dtkAbstractData;
class dtkAbstractProcess;
class dtkAbstractView;

class dtkScriptInterpreterPrivate;

class DTKSCRIPT_EXPORT dtkScriptInterpreter : public QObject
{
    Q_OBJECT

public:
             dtkScriptInterpreter(QObject *parent = 0);
    virtual ~dtkScriptInterpreter(void);

    enum Status {
        Status_Ok,
        Status_Error,
        Status_Return,
        Status_Break,
        Status_Continue
    };

    void retain(void);
    void release(void);

    void registerPrompt(char *(*prompt)(void));

    virtual void registerVariable(bool   &var, QString name, QString description = "") = 0;
    virtual void registerVariable(int    &var, QString name, QString description = "") = 0;
    virtual void registerVariable(double &var, QString name, QString description = "") = 0;
    virtual void registerVariable(char * &var, QString name, QString description = "") = 0;

    virtual void unregisterVariable(QString name) = 0;

    void setVerbose(bool verbose);

    QString prompt(void) const;

public slots:
    void load(const QString& file);
    void save(const QString& file);

    void start(void);
    void stop(void);

    virtual QString interpret(const QString& command, int *stat) = 0;
    virtual QString interpret(const QString& command, const QStringList& args, int *stat) = 0;

    QString help(void) const;

signals:
    void interpreted(const QString& result, int *stat);
    void stopped(void);

protected:
    void registerVariableDescription(QString name, QString description);
    void registerFunctionDescription(QString name, QString description);

    void unregisterVariableDescription(QString name);
    void unregisterFunctionDescription(QString name);

private:
    dtkScriptInterpreterPrivate *d;
};

#endif
