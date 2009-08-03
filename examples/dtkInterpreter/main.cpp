/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sat Apr 11 13:49:30 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Fri May 15 11:08:18 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 17
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

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    AnyOption options;
    options.addUsage("Usage: ./dtkInterpreter [FLAG] ... [OPTION=VALUE] ...");
    options.addUsage("");
    options.addUsage("Script:");
    options.addUsage(" -i  --interpreter");
    options.addUsage("     --interpreter=tcl    Run tcl     gui interpreter");
    options.addUsage("     --interpreter=python Run python  gui interpreter");

    options.setOption("interpreter", 'i');

    options.processCommandArgs(argc, argv);

    tstMainWindow window;

    if (options.getValue("interpreter") != NULL || options.getValue('i') != NULL) {

        dtkScriptInterpreter *interpreter;

        if(QString(options.getValue('i')) == "python")
            interpreter = new dtkScriptInterpreterPython;
        else
            interpreter = new dtkScriptInterpreterTcl;

        window.interpreter()->registerInterpreter(interpreter);

        QObject::connect(interpreter, SIGNAL(stopped()), &application, SLOT(quit()));
	QObject::connect(&application, SIGNAL(aboutToQuit()), interpreter, SLOT(stop()));
    } else {
        options.printUsage();
        return 0;
    }

    window.show();

    return application.exec();
}
