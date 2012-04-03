/* dtkScriptInterpreter.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Nov 26 16:11:10 2008 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Apr  3 16:01:44 2012 (+0200)
 *           By: tkloczko
 *     Update #: 459
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 21-Jan-2009    Julien Wintz  
 *    Last-Updated: Wed Jan 21 13:32:00 2009 (+0100) #187 (Julien Wintz)
 *    Thread safe synchronizer implementation.
 * 21-Jan-2009    Julien Wintz  
 *    Last-Updated: Wed Jan 21 11:30:47 2009 (+0100) #185 (Julien Wintz)
 *    Separating histedit from interprer itself.
 */

#include <iostream>

#ifdef HAVE_EDITLINE
#include <histedit.h>
#endif

#include <dtkCore/dtkPluginManager.h>

#include <dtkScript/dtkScriptInterpreter.h>

// /////////////////////////////////////////////////////////////////
// dtkScriptInterpreterSynchronizer
// /////////////////////////////////////////////////////////////////

dtkScriptInterpreterSynchronizer *dtkScriptInterpreterSynchronizer::instance(void)
{
    static QMutex m_mutex;

    m_mutex.lock();
    if(!m_instance)
	m_instance = new dtkScriptInterpreterSynchronizer;
    m_mutex.unlock();

    return m_instance;
}

void dtkScriptInterpreterSynchronizer::lock(void)
{
    mutex->lock();
}

void dtkScriptInterpreterSynchronizer::unlock(void)
{
    mutex->unlock();
}

void dtkScriptInterpreterSynchronizer::wait(void)
{
    condition->wait(mutex);
}

void dtkScriptInterpreterSynchronizer::wake(void)
{
    condition->wakeOne();
}

dtkScriptInterpreterSynchronizer::dtkScriptInterpreterSynchronizer(void)
{
    mutex = new QMutex;
    condition = new QWaitCondition;
}

dtkScriptInterpreterSynchronizer::~dtkScriptInterpreterSynchronizer(void)
{
    delete mutex;
    delete condition;
}

dtkScriptInterpreterSynchronizer *dtkScriptInterpreterSynchronizer::m_instance = NULL;

// /////////////////////////////////////////////////////////////////
// dtkScriptInterpreterConsolePrivate
// /////////////////////////////////////////////////////////////////

class dtkScriptInterpreterConsolePrivate
{
public:
    char *(*prompt)(void);

#ifdef HAVE_EDITLINE
    EditLine *el_engine;
    History  *el_history;
    HistEvent el_event;
#endif
};

// /////////////////////////////////////////////////////////////////
// dtkScriptInterpreterConsole
// /////////////////////////////////////////////////////////////////

dtkScriptInterpreterConsole::dtkScriptInterpreterConsole(QObject *parent) : QThread(parent), d(new dtkScriptInterpreterConsolePrivate)
{

}

dtkScriptInterpreterConsole::~dtkScriptInterpreterConsole(void)
{
    delete d;

    d = NULL;
}

void dtkScriptInterpreterConsole::registerPrompt(char *(*prompt)(void))
{
    d->prompt = prompt;
}

void dtkScriptInterpreterConsole::registerBindings(QString style)
{
    DTK_UNUSED(style);

#ifdef HAVE_EDITLINE
    el_set(d->el_engine, EL_EDITOR, style.toAscii().constData());    
#endif
}

QString dtkScriptInterpreterConsole::prompt(void) const
{
    return QString(d->prompt());
}

void dtkScriptInterpreterConsole::start(Priority priority)
{
    DTK_UNUSED(priority);

#ifdef HAVE_EDITLINE
    d->el_engine = el_init("dtkScriptInterpreter", stdin, stdout, stderr);
    el_set(d->el_engine, EL_PROMPT, d->prompt);
    el_set(d->el_engine, EL_EDITOR, "emacs");
    
    d->el_history = history_init();
    if (!d->el_history)
	qFatal("Could not initialize editline history");
    history(d->el_history, &(d->el_event), H_SETSIZE, 800);
    el_set(d->el_engine, EL_HIST, history, d->el_history);

    QThread::start(priority);
#endif
}

void dtkScriptInterpreterConsole::stop(void)
{
#ifdef HAVE_EDITLINE
    if(this->isRunning()) {
        std::cerr << "bye" << std::endl;
        if (d->el_history) {
            history_end(d->el_history);
            d->el_history = 0l;
        }
        if (d->el_engine) {
            el_end(d->el_engine);
            d->el_engine = 0l;
        }
    }

    quit();
    wait(0);
#endif
}

void dtkScriptInterpreterConsole::run(void)
{
#ifdef HAVE_EDITLINE
    int count;
    int stat;

    forever {

        QString line = QString(el_gets(d->el_engine, &count)).simplified();
           
        if (line == "bye" || line == "exit" || line == "quit")
            break;
        
        if(line != "")
            history(d->el_history, &(d->el_event), H_ENTER, line.toAscii().constData());

        dtkScriptInterpreterSynchronizer::instance()->lock();

        if (line.startsWith(":load ")) {
            emit load(line.remove(":load "));

        } else if (line.startsWith(":save ")) {
            emit save(line.remove(":save "));

        } else if (line.startsWith(":emacs")) {
            std::cerr << "switching to emacs bindings" << std::endl;

            registerBindings("emacs");

            emit input("", &stat);

        } else if (line.startsWith(":vi")) {
            std::cerr << "switching to vi bindings" << std::endl;

            registerBindings("vi");

            emit input("", &stat);

        } else if (line.startsWith(":plugins")) {
            dtkPluginManager::instance()->printPlugins();

            emit input("", &stat);

        } else if (line.startsWith(":help")) {
            std::cerr << "Plugins:" << std::endl;
            std::cerr << " :plugins            prints the status of plugins" << std::endl;
            std::cerr << "" << std::endl;
            std::cerr << "File manipulation:" << std::endl;
            std::cerr << " :load [file]        loads file and interprets its content" << std::endl;
            std::cerr << " :save [file]        saves interpreter history to file" << std::endl;
            std::cerr << "" << std::endl;
            std::cerr << "Keyboard bindings:" << std::endl;
            std::cerr << " :emacs              sets up emacs key bindings" << std::endl;
            std::cerr << " :vi                 sets up vi    key bindings" << std::endl;
            std::cerr << "" << std::endl;
            std::cerr << "Documentation:" << std::endl;
            std::cerr << " :man [page]         displays documentation for page" << std::endl;
            std::cerr << "" << std::endl;

            emit input("", &stat);

        } else if (line.startsWith(":man ")) {
            
#if defined(Q_OS_MAC) || defined(Q_OS_UNIX)
            QString program = "man";
        
            QStringList arguments;
            arguments << "-P";
            arguments << "cat";
            arguments << "-M";
            arguments << "../doc/man";
            arguments << line.remove(":man ");

            stat = dtkScriptInterpreter::Status_Ok;
        
            QProcess process;	    
            process.start(program, arguments);
            process.waitForFinished(-1);

            emit output(QString(process.readAll()), &stat);
#endif

            emit input("", &stat);

        } else if (count > 0) {
            
            emit input(line, &stat);

        }

        dtkScriptInterpreterSynchronizer::instance()->wait();
        dtkScriptInterpreterSynchronizer::instance()->unlock();
    }

    if (d->el_history) {
        history_end(d->el_history);
        d->el_history = 0l;
    }
    if (d->el_engine) {
        el_end(d->el_engine);
        d->el_engine = 0l;
    }

    emit stopped();
#endif
}

#include <iostream>

void dtkScriptInterpreterConsole::output(const QString& result, int *stat)
{
    if(!result.simplified().isEmpty())
	std::cout << (*stat == dtkScriptInterpreter::Status_Ok ? DTK_NO_COLOR : DTK_COLOR_FG_RED) << result.toAscii().constData() << DTK_NO_COLOR << std::endl;
}

// /////////////////////////////////////////////////////////////////
// dtkScriptInterpreterPrivate
// /////////////////////////////////////////////////////////////////

class dtkScriptInterpreterPrivate
{
public:
    QMap<QString, QString> variableDescription;
    QMap<QString, QString> functionDescription;

#ifndef Q_OS_WIN32
    dtkScriptInterpreterConsole *console;
#endif

    int count;
};

// /////////////////////////////////////////////////////////////////
// dtkScriptInterpreter
// /////////////////////////////////////////////////////////////////

dtkScriptInterpreter::dtkScriptInterpreter(QObject *parent) : QObject(parent), d(new dtkScriptInterpreterPrivate)
{
    d->count = 1;

#ifndef Q_OS_WIN32
    d->console = new dtkScriptInterpreterConsole(this);

    connect(this, SIGNAL(interpreted(const QString&, int *)), d->console, SLOT(output(const QString&, int *)));
    connect(d->console, SIGNAL(input(const QString&, int *)), this,    SLOT(interpret(const QString&, int *)));
    connect(d->console, SIGNAL( load(const QString&)),        this,    SLOT(     load(const QString&)));
    connect(d->console, SIGNAL( save(const QString&)),        this,    SLOT(     save(const QString&)));
    connect(d->console, SIGNAL(stopped(void)),                this,  SIGNAL(  stopped(void)));
#endif
}

void dtkScriptInterpreter::retain(void)
{
    d->count++;
}

void dtkScriptInterpreter::release(void)
{
    if(!(--(d->count)))
	delete this;
}

QString dtkScriptInterpreter::help(void) const
{
    QString message;

    message += "Functions:\n";
    foreach(QString name, d->functionDescription.keys())
	message += "\t" + name + ": " + d->functionDescription.value(name) + "\n";

    message += "Variables:\n";
    foreach(QString name, d->variableDescription.keys())
	message += "\t" + name + ": " + d->variableDescription.value(name) + "\n";

    return message;
}

void dtkScriptInterpreter::load(const QString& file)
{
    int stat;
    QFile script(file);
    QString commands;

    script.open(QFile::ReadOnly);
    commands = QLatin1String(script.readAll());
    script.close() ;
    
    interpret(commands, &stat);
}

void dtkScriptInterpreter::save(const QString& file)
{
    DTK_UNUSED(file);
}

void dtkScriptInterpreter::registerPrompt(char *(*prompt)(void))
{
#ifndef Q_OS_WIN32
    d->console->registerPrompt(prompt);
#endif
}

void dtkScriptInterpreter::registerVariableDescription(QString name, QString description)
{
    d->variableDescription.insert(name, description);
}

void dtkScriptInterpreter::registerFunctionDescription(QString name, QString description)
{
    d->functionDescription.insert(name, description);
}

void dtkScriptInterpreter::unregisterVariableDescription(QString name)
{
    d->functionDescription.remove(name);
}

void dtkScriptInterpreter::unregisterFunctionDescription(QString name)
{
    d->functionDescription.remove(name);
}

QString dtkScriptInterpreter::prompt(void) const
{
#ifndef Q_OS_WIN32
    return d->console->prompt();
#else
	return "interpreter:~$";
#endif
}

void dtkScriptInterpreter::start(void)
{
#ifndef Q_OS_WIN32
	d->console->start();
#endif
}

void dtkScriptInterpreter::stop(void)
{
#ifndef Q_OS_WIN32
	d->console->stop();
#endif
}

void dtkScriptInterpreter::setVerbose(bool verbose)
{
#ifndef Q_OS_WIN32
    if(verbose)
	   connect(this, SIGNAL(interpreted(const QString&, int *)), d->console, SLOT(output(const QString&, int *)));
    else
	disconnect(this, SIGNAL(interpreted(const QString&, int *)), d->console, SLOT(output(const QString&, int *)));    
#endif
}

dtkScriptInterpreter::~dtkScriptInterpreter(void)
{
#ifndef Q_OS_WIN32
    d->console->stop();
#endif

    delete d;
}
