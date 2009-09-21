/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sat Apr 11 13:49:30 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Mon Sep 21 11:31:43 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 34
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <QtGui/QApplication>

#include "anyoption.h"

#include "tstMainWindow.h"

#include <dtkScript/dtkScriptInterpreter.h>
#include <dtkScript/dtkScriptInterpreterTcl.h>
#include <dtkScript/dtkScriptInterpreterPython.h>

#include <dtkGui/dtkInterpreter.h>

// /////////////////////////////////////////////////////////////////
// log message handler
// /////////////////////////////////////////////////////////////////

QWidget *log_output;

void tstRedirectLogHandler(dtkLog::Level level, const QString& msg)
{
    QCoreApplication::postEvent(log_output, new dtkLogEvent(level, msg));
}

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    AnyOption options;
    options.addUsage("Usage: ./dtkInterpreter [FLAG] ... [OPTION=VALUE] ...");
    options.addUsage("");
    options.addUsage("Mode:");
    options.addUsage(" -c  --console");
    options.addUsage("");
    options.addUsage("Script:");
    options.addUsage(" -i  --interpreter");
    options.addUsage("     --interpreter=tcl    Run tcl     gui interpreter");
    options.addUsage("     --interpreter=python Run python  gui interpreter");


    options.setFlag("console", 'c');
    options.setOption("interpreter", 'i');

    options.processCommandArgs(argc, argv);

    tstMainWindow window;

    if (options.getValue("interpreter") != NULL || options.getValue('i') != NULL) {

        dtkScriptInterpreter *interpreter;

        if(QString(options.getValue('i')) == "python")
            interpreter = new dtkScriptInterpreterPython;
        else
            interpreter = new dtkScriptInterpreterTcl;

        if(!options.getFlag("console") || !options.getFlag('c')) {

            log_output = window.interpreter();

            window.interpreter()->registerInterpreter(interpreter);
            window.interpreter()->registerAsHandler(tstRedirectLogHandler);
            window.show();
        } else {
            interpreter->start();
        }

        QObject::connect(interpreter, SIGNAL(stopped()), &application, SLOT(quit()));
	QObject::connect(&application, SIGNAL(aboutToQuit()), interpreter, SLOT(stop()));
    } else {
        options.printUsage();
        return 0;
    }

    return application.exec();
}
