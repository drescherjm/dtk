/* dtkCreator.i --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Aug  6 16:07:45 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Aug  6 20:15:49 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 24
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

%module creator
%{
#undef  T_DATA

#include <QtDebug>
#include <QtCore>
#include <QtGui>

#include "dtkCreatorController.h"
#include "dtkCreatorPluginBrowser.h"
#include "dtkCreatorScriptBrowser.h"
#include "dtkCreatorViewer.h"
#include "dtkCreatorWidgetFactory.h"
%}

#pragma SWIG nowarn=401, 801

#undef Q_OBJECT
#undef Q_PROPERTY(text)
#undef signals
#udnef slots

#define Q_OBJECT
#define Q_PROPERTY(text)
#define signals public
#define slots

#ifdef SWIGPYTHON
%typemap(in) QString { // Python -> C++
    $1 = QString(PyString_AsString($input));
}

%typemap(out) QString { // C++ -> Python
    $result = PyString_FromString($1.toAscii().constData());
}
#elif SWIGTCL
%typemap(in) QString { // Tcl -> C++
    $1 = QString(Tcl_GetString($input));
}

%typemap(out) QString { // C++ -> Tcl
    Tcl_SetStringObj($result, $1.toAscii().constData(), $1.size());
}
#endif

// /////////////////////////////////////////////////////////////////
// Ignore signals
// /////////////////////////////////////////////////////////////////

%ignore dtkCreatorPluginList::pluginClicked(QWidget *);
%ignore dtkCreatorScriptList::loaded(const QString&);
%ignore dtkCreatorWidgetFactory::interpret(const QString&, int *stat);
%ignore dtkCreatorWidgetFactoryButton::interpret(const QString&, int *stat);

// /////////////////////////////////////////////////////////////////
// Input
// /////////////////////////////////////////////////////////////////

%include "dtkCreatorController.h"
%include "dtkCreatorPluginBrowser.h"
%include "dtkCreatorScriptBrowser.h"
%include "dtkCreatorViewer.h"
%include "dtkCreatorWidgetFactory.h"
