/* dtkVr.i --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Wed Jan 13 14:21:12 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Mar  2 13:35:03 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 47
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKVR_I
#define DTKVR_I

%module vr
%{
#include <dtkVr/dtkVrDevice.h>
#if defined(DTK_WRAP_VR)
#include <dtkVr/dtkVrManager.h>
#include <dtkVr/dtkVrMaster.h>
#include <dtkVr/dtkVrProcess.h>
#include <dtkVr/dtkVrSlave.h>
#endif
#include <dtkVr/dtkVrTracker.h>

#include <QtDebug>
#include <QtCore>
%}

// /////////////////////////////////////////////////////////////////
// Preprocessing setup
// /////////////////////////////////////////////////////////////////

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

#undef  DTKVR_EXPORT
#define DTKVR_EXPORT

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

%include <dtkVr/dtkVrDevice.h>
#if defined(DTK_WRAP_VR)
%include <dtkVr/dtkVrManager.h>
%include <dtkVr/dtkVrMaster.h>
%include <dtkVr/dtkVrProcess.h>
%include <dtkVr/dtkVrSlave.h>
#endif
%include <dtkVr/dtkVrTracker.h>

#endif
