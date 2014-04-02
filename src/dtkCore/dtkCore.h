/* dtkCore.h --- 
 * 
 * Author: Julien Wintz
 * Created: Thu Feb 28 16:28:31 2013 (+0100)
 * Version: 
 * Last-Updated: mar. avril  1 14:26:46 2014 (+0200)
 *           By: Thibaud Kloczko
 *     Update #: 28
 */

/* Change Log:
 * 
 */

#pragma once

#include <QtCore>

// ///////////////////////////////////////////////////////////////////
// SFINAE trick to know whether an object derived from dtkCoreObject or not
// ///////////////////////////////////////////////////////////////////

template<typename T> class IsPointerToTypeDerivedFromCoreObject
{
public:
    enum { Value = false };
};

// Specialize to avoid sizeof(void) warning
template<> class IsPointerToTypeDerivedFromCoreObject<void *>
{
public:
    enum { Value = false };
};

/* template<> class IsPointerToTypeDerivedFromQObject<dtkCoreObject*> */
/* { */
/*     enum { Value = true }; */
/* }; */

class dtkCoreObject;

template<typename T> class IsPointerToTypeDerivedFromCoreObject<T *>
{
    typedef qint8 dtk_yes_type;
    typedef qint64 dtk_no_type;

    static dtk_yes_type checkType(dtkCoreObject *);
    static dtk_no_type  checkType(...);

public:
    enum { Value = sizeof(checkType(static_cast<T *>(0))) == sizeof(dtk_yes_type) };
};
