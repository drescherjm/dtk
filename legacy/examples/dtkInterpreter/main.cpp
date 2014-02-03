/* main.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sat Apr 11 13:49:30 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Jan 10 14:39:48 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 117
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include <dtkConfig.h>
#include <dtkLog/dtkLog.h>
#include <dtkScript/dtkScriptInterpreter.h>
#if defined(DTK_BUILD_WRAPPERS) && defined(DTK_HAVE_TCL)
#include <dtkScript/dtkScriptInterpreterTcl.h>
#endif
#if defined(DTK_BUILD_WRAPPERS) && defined(DTK_HAVE_PYTHON)
#include <dtkScript/dtkScriptInterpreterPython.h>
#endif
#include <dtkGui/dtkInterpreter.h>

#include <QtGui>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    application.setOrganizationDomain("fr");
    application.setOrganizationName("inria");
    application.setApplicationName("dtkInterpreter");

    dtkLogger::instance().setLevel(dtkLog::Trace);

    dtkInterpreter interpreter;
    interpreter.show();
    interpreter.raise();

#if defined(DTK_BUILD_WRAPPERS) && defined(DTK_HAVE_PYTHON)
    if(application.arguments().contains("-python"))
        interpreter.registerInterpreter(new dtkScriptInterpreterPython(&interpreter));
#endif

#if defined(DTK_BUILD_WRAPPERS) && defined(DTK_HAVE_TCL)
    if(application.arguments().contains("-tcl"))
        interpreter.registerInterpreter(new dtkScriptInterpreterTcl(&interpreter));
#endif
    
    return application.exec();
}
