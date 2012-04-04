/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sat Apr 11 13:49:30 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Wed Apr  4 10:28:40 2012 (+0200)
 *           By: tkloczko
 *     Update #: 46
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
#if defined(HAVE_SWIG) && defined(HAVE_TCL)
#include <dtkScript/dtkScriptInterpreterTcl.h>
#endif
#if defined(HAVE_SWIG) && defined(HAVE_PYTHON)
#include <dtkScript/dtkScriptInterpreterPython.h>
#endif

#include <dtkGui/dtkInterpreter.h>

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

        dtkScriptInterpreter *interpreter = NULL;

#if defined(HAVE_SWIG) && defined(HAVE_PYTHON)
        if(QString(options.getValue('i')) == "python")
            interpreter = new dtkScriptInterpreterPython;
#endif

#if defined(HAVE_SWIG) && defined(HAVE_TCL)
        if(QString(options.getValue('i')) == "tcl")
            interpreter = new dtkScriptInterpreterTcl;
#endif

        if(!interpreter) {
            qDebug() << "No interpreter available. Is BUILD_WRAPPERS enabled ?";
            return 0;
        }

        if(!options.getFlag("console") || !options.getFlag('c')) {

            window.interpreter()->registerInterpreter(interpreter);
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
