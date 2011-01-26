/* dtkCore.i --- Core layer swig interface definition
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Jan  6 21:45:15 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Dec 24 13:31:50 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 317
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
%include "carrays.i"
%array_class(double, doubleArray);
%{
#include <QtDebug>
#include <QtCore>

#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractDataFactory.h>
#include <dtkCore/dtkAbstractDataMesh.h>
#include <dtkCore/dtkAbstractDataReader.h>
#include <dtkCore/dtkAbstractDataWriter.h>
#include <dtkCore/dtkAbstractDataConverter.h>
#include <dtkCore/dtkAbstractDataImage.h>
#include <dtkCore/dtkAbstractObject.h>
#include <dtkCore/dtkAbstractProcess.h>
#include <dtkCore/dtkAbstractProcessFactory.h>
#include <dtkCore/dtkAbstractView.h>
#include <dtkCore/dtkAbstractViewAnimator.h>
#include <dtkCore/dtkAbstractViewFactory.h>
#include <dtkCore/dtkAbstractViewInteractor.h>
#include <dtkCore/dtkAbstractViewNavigator.h>
#include <dtkCore/dtkPlugin.h>
#include <dtkCore/dtkPluginManager.h>
#include <dtkCore/dtkVec3.h>
#include <dtkCore/dtkQuat.h>
%}

// /////////////////////////////////////////////////////////////////
// Preprocessing setup
// /////////////////////////////////////////////////////////////////

#pragma SWIG nowarn=389, 401, 509, 801, 472

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

#undef  Q_DECLARE_METATYPE(Type type)
#define Q_DECLARE_METATYPE(Type type)

#undef  DTKCORE_EXPORT
#define DTKCORE_EXPORT

// /////////////////////////////////////////////////////////////////
// Ignore rules for operators
// /////////////////////////////////////////////////////////////////

%ignore operator>>;
%ignore operator<<;
%ignore operator==;
%ignore operator[];
%ignore operator!=;
%ignore operator*=;
%ignore operator/=;
%ignore operator bool;
%ignore operator int;
%ignore operator float;
%ignore operator double;
%ignore operator double *;

// /////////////////////////////////////////////////////////////////
// Ignore rules for dtkAbstractObject signals
// /////////////////////////////////////////////////////////////////

%ignore addProperty(const QString& key, const QStringList& values); // No scripter should add properties dynamically
%ignore addProperty(const QString& key, const QString& value);      // No scripter should add properties dynamically

%ignore propertySet(const QString& key, const QString& value);
%ignore metaDataSet(const QString& key, const QString& value);

// /////////////////////////////////////////////////////////////////
// Ignore rules for dtkAbstractDataReader|Writer|Process
// /////////////////////////////////////////////////////////////////

%ignore started(const QString& message);
%ignore elapsed(const QString& duration);
%ignore progressed(int step);
%ignore progressed(const QString& message);
%ignore success();
%ignore failure();
%ignore finished();
%ignore success();
%ignore failure();

// /////////////////////////////////////////////////////////////////
// Ignore rules for dtkAbstractView signals
// /////////////////////////////////////////////////////////////////

%ignore closed();

// /////////////////////////////////////////////////////////////////
// Ignore rules for dtkAbstractViewInteractor signals
// /////////////////////////////////////////////////////////////////

%ignore updated();

// /////////////////////////////////////////////////////////////////
// Ignore rules for factories
// /////////////////////////////////////////////////////////////////

%ignore created(dtkAbstractData *data, const QString& type);
%ignore created(dtkAbstractProcess *process,const  QString& type);
%ignore created(dtkAbstractView *view, const QString& type);

// /////////////////////////////////////////////////////////////////
// Ignore rules for dtkPluginManager
// /////////////////////////////////////////////////////////////////

%ignore   loaded(const QString& path);
%ignore unloaded(const QString& path);

// /////////////////////////////////////////////////////////////////
// Typemaps
// /////////////////////////////////////////////////////////////////

#ifdef SWIGPYTHON

%typecheck(SWIG_TYPECHECK_STRING) char * {
  $1 = PyString_Check($input) ? 1 : 0;
}

%typemap(typecheck)       QString  = char *;
%typemap(typecheck) const QString& = char *;
%typemap(typecheck) QStringList = char *;
%typemap(typecheck) const QStringList& = char *;

// Python -> C++

%typemap(in) QString {
    if (PyString_Check($input)) {
         $1 = QString(PyString_AsString($input));
     } else {
         qDebug("QString expected");
     }
}

%typemap(in) const QString& {
    if (PyString_Check($input)) {
         char *t = PyString_AsString($input);
         $1 = new QString(t);
     } else {
         qDebug("QString expected");
     }
}

%typemap(in) QStringList {
    if (PyList_Check($input)) {
        int i = 0;
        int end = PyList_Size($input);
        for(i;i!=end; ++i) {
            $1 << QString(PyString_AsString(PyList_GET_ITEM($input, i)));
            } 
        }
    else {
        qDebug("QStringList expected");
    }
}

%typemap(in) const QStringList& {
    if (PyList_Check($input)) {
        int i = 0;
        int end = PyList_Size($input);
        $1 = new QStringList;
        for(i;i!=end; ++i) {
            char *t = PyString_AsString(PyList_GET_ITEM($input, i));
            (*$1) << QString(t);
            } 
        }
    else {
        qDebug("QStringList expected");
    }
}
// C++ -> Python

%typemap(out) QString {
    $result = PyString_FromString($1.toAscii().constData());
}

%typemap(out) const QString& {
    $result = PyString_FromString($1.toAscii().constData());
}

// Typemaps for QList
%define %QList_typemapsPtr(DATA_TYPE)
 
%typemap(out) QList<DATA_TYPE> {
  $result = PyList_New($1.size());
  int i = 0;
  QList<DATA_TYPE>::iterator it = $1.begin(); 
  QList<DATA_TYPE>::iterator end = $1.end(); 
  for(;it!=end; ++it, ++i)  {
    PyObject* obj = SWIG_NewPointerObj((*it), $descriptor(DATA_TYPE), 0|0);
    PyList_SET_ITEM($result, i, obj);
  }
}

%enddef // %QList_typemapsPtr() 

%QList_typemapsPtr(dtkPlugin *)


// Typemaps for QList
%define %QList_typemaps(DATA_TYPE)
 
%typemap(out) QList<DATA_TYPE> {
  $result = PyList_New($1.size());
  int i = 0;
  QList<DATA_TYPE>::iterator it = $1.begin(); 
  QList<DATA_TYPE>::iterator end = $1.end(); 
  for(;it!=end; ++it, ++i)  {
    DATA_TYPE *newItem = new DATA_TYPE(*it);
    PyObject* obj = SWIG_NewPointerObj(newItem, $descriptor(DATA_TYPE*), 0|0);
    PyList_SET_ITEM($result, i, obj);
  }
}

%enddef // %QList_typemaps()


// Typemaps for QStringList
%typemap(out) QStringList {
    $result = PyList_New($1.size());
    int i = 0;
    QStringList::iterator it = $1.begin();
    QStringList::iterator end = $1.end();
    for(;it!=end; ++it, ++i) {
        PyObject* st = PyString_FromString((*it).toAscii().constData());
        PyList_SET_ITEM($result, i, st);
  }
}

// Copy of the code for QStringList
%typemap(out) QList<QString> {
    $result = PyList_New($1.size());
    int i = 0;
    QStringList::iterator it = $1.begin();
    QStringList::iterator end = $1.end();
    for(;it!=end; ++it, ++i) {
        PyObject* st = PyString_FromString((*it).toAscii().constData());
        PyList_SET_ITEM($result, i, st);
  }
}

template <class T1, class T2>
class QPair
{
public:
    T1 first;
    T2 second;
};

// Typemaps for dtkAbstractDataFactory::dtkAbstractDataTypeHandler
%define %QPair_typemaps(DATA_TYPE_1, DATA_TYPE_2)
 
%typemap(out) QPair<DATA_TYPE_1, DATA_TYPE_2> {
  $result = PyTuple_New(2);
  PyObject* obj1 = SWIG_NewPointerObj(*$1.first, $descriptor(DATA_TYPE_1), 0|0);
  PyObject* obj2 = SWIG_NewPointerObj(*$1.second, $descriptor(DATA_TYPE_2), 0|0);
  PyTuple_SET_ITEM($result, 0, obj1);
  PyTuple_SET_ITEM($result, 1, obj2);
}

%enddef // %QPair_typemaps()

%template(QPairStrStrList) QPair<QString, QStringList>;
%QPair_typemaps(QString,QStringList)

%QList_typemaps(dtkAbstractDataFactory::dtkAbstractDataTypeHandler)

#elif SWIGTCL

// Tcl -> C++

%typemap(in) QString {
    $1 = QString(Tcl_GetString($input));
}

%typemap(in) const QString& {
    char *t = Tcl_GetString($input);
    $1 = new QString(t);
}

// C++ -> Tcl

%typemap(out) QString { 
    Tcl_SetStringObj($result, $1.toAscii().constData(), $1.size());
}

%typemap(out) const QString& {
    Tcl_SetStringObj($result, $1.toAscii().constData(), $1.size());
}

#endif

// /////////////////////////////////////////////////////////////////
// Wrapper input
// /////////////////////////////////////////////////////////////////

%include <dtkCore/dtkAbstractObject.h>

%include <dtkCore/dtkAbstractData.h>
%include <dtkCore/dtkAbstractDataMesh.h>
%include <dtkCore/dtkAbstractDataFactory.h>
%include <dtkCore/dtkAbstractDataReader.h>
%include <dtkCore/dtkAbstractDataWriter.h>
%include <dtkCore/dtkAbstractDataConverter.h>
%include <dtkCore/dtkAbstractDataImage.h>
%include <dtkCore/dtkAbstractProcess.h>
%include <dtkCore/dtkAbstractProcessFactory.h>
%include <dtkCore/dtkAbstractView.h>
%include <dtkCore/dtkAbstractViewFactory.h>
%include <dtkCore/dtkAbstractViewAnimator.h>
%include <dtkCore/dtkAbstractViewInteractor.h>
%include <dtkCore/dtkAbstractViewNavigator.h>
%include <dtkCore/dtkPlugin.h>
%include <dtkCore/dtkPluginManager.h>
%include <dtkCore/dtkVec3.h>
%include <dtkCore/dtkQuat.h>

#ifdef SWIGPYTHON

// /////////////////////////////////////////////////////////////////
// Helper functions
// /////////////////////////////////////////////////////////////////

%inline %{

dtkAbstractDataMesh *dtk_as_mesh(dtkAbstractData *data)
{
    return dynamic_cast<dtkAbstractDataMesh *>(data);
}

%}

#endif

#endif
