/* dtkCore.i --- Core layer swig interface definition
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Jan  6 21:45:15 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Oct  5 23:01:20 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 199
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKCORE_I
#define DTKCORE_I

%module core
%{
#include <QtDebug>
#include <QtCore>

#include <dtkCore/dtkAbstractObject.h>

#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractDataReader.h>
#include <dtkCore/dtkAbstractDataWriter.h>

#include <dtkCore/dtkAbstractDataImage.h>

#include <dtkCore/dtkAbstractProcess.h>

#include <dtkCore/dtkAbstractView.h>
#include <dtkCore/dtkAbstractViewAnimator.h>
#include <dtkCore/dtkAbstractViewInteractor.h>
#include <dtkCore/dtkAbstractViewNavigator.h>

#include <dtkCore/dtkAbstractDevice.h>

#include <dtkCore/dtkAbstractFactory.h>
#include <dtkCore/dtkAbstractDataFactory.h>
#include <dtkCore/dtkAbstractDeviceFactory.h>
#include <dtkCore/dtkAbstractProcessFactory.h>
#include <dtkCore/dtkAbstractViewFactory.h>

#include <dtkCore/dtkPlugin.h>

#include <dtkCore/dtkPluginManager.h>
%}

// /////////////////////////////////////////////////////////////////
// Preprocessing setup
// /////////////////////////////////////////////////////////////////

// 401:
// 509:
// 801:
#pragma SWIG nowarn=401, 509, 801, 472

// /////////////////////////////////////////////////////////////////
// Macro undefinition
// /////////////////////////////////////////////////////////////////

#undef Q_OBJECT
#undef signals
#undef slots

#define Q_OBJECT
#define signals public
#define slots

#undef  Q_PROPERTY(Type type MODE mode)
#define Q_PROPERTY(Type type MODE mode)

#undef  Q_DECLARE_INTERFACE(IFace, IId)
#define Q_DECLARE_INTERFACE(IFace, IId)

#undef  DTKCORE_EXPORT
#define DTKCORE_EXPORT

// /////////////////////////////////////////////////////////////////
// Ignore rules for operators
// /////////////////////////////////////////////////////////////////

%ignore operator<<;
%ignore operator==;

// /////////////////////////////////////////////////////////////////
// Ignore rules for dtkAbstractObject signals
// /////////////////////////////////////////////////////////////////

%ignore addProperty(QString key, QStringList values); // No scripter should add properties dynamically
%ignore addProperty(QString key, QString value);      // No scripter should add properties dynamically

%ignore propertySet(QString key, QString value);
%ignore metadataSet(QString key, QString value);

// /////////////////////////////////////////////////////////////////
// Ignore rules for dtkAbstractView signals
// /////////////////////////////////////////////////////////////////

%ignore selected(dtkAbstractData *);

%ignore clickedScreenCoordinates(int, int);

%ignore clickedObjectCoordinates(double, double);
%ignore clickedObjectCoordinates(double, double, double);

%ignore clickedWorldCoordinates(double, double);
%ignore clickedWorldCoordinates(double, double, double);

// /////////////////////////////////////////////////////////////////
// Ignore rules for dtkAbstractDevice signals
// /////////////////////////////////////////////////////////////////

%ignore buttonPressed(int idx);
%ignore buttonReleased(int idx);

// /////////////////////////////////////////////////////////////////
// Ignore rules for dtkAbstractViewInteractor signals
// /////////////////////////////////////////////////////////////////

%ignore updated();

// /////////////////////////////////////////////////////////////////
// Ignore rules for factories
// /////////////////////////////////////////////////////////////////

%ignore created(dtkAbstractData *data, QString type);
%ignore created(dtkAbstractProcess *process, QString type);
%ignore created(dtkAbstractView *view, QString type);

// /////////////////////////////////////////////////////////////////
// Typemaps
// /////////////////////////////////////////////////////////////////

#ifdef SWIGPYTHON

%typecheck(SWIG_TYPECHECK_STRING) char * {
  $1 = PyString_Check($input) ? 1 : 0;
}

%typemap(typecheck) QString = char *;

%typemap(in) QString { // Python -> C++
    if (PyString_Check($input)) {
         $1 = QString(PyString_AsString($input));
     } else {
         qDebug("QString expected");
     }
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
// Wrapper input
// /////////////////////////////////////////////////////////////////

%include <dtkCore/dtkAbstractObject.h>

%include <dtkCore/dtkAbstractData.h>
%include <dtkCore/dtkAbstractDataFactory.h>
%include <dtkCore/dtkAbstractDataReader.h>
%include <dtkCore/dtkAbstractDataWriter.h>

%include <dtkCore/dtkAbstractDataImage.h>

%include <dtkCore/dtkAbstractProcess.h>
%include <dtkCore/dtkAbstractProcessFactory.h>

%include <dtkCore/dtkAbstractDevice.h>
%include <dtkCore/dtkAbstractDeviceFactory.h>

%include <dtkCore/dtkAbstractView.h>
%include <dtkCore/dtkAbstractViewFactory.h>
%include <dtkCore/dtkAbstractViewAnimator.h>
%include <dtkCore/dtkAbstractViewInteractor.h>
%include <dtkCore/dtkAbstractViewNavigator.h>

%include <dtkCore/dtkPlugin.h>
%include <dtkCore/dtkPluginManager.h>

#endif
