/* dtkCore.h --- 
 * 
 * Author: Julien Wintz
 * Created: Thu Feb 28 16:28:31 2013 (+0100)
 * Version: 
 * Last-Updated: Thu Mar 21 15:11:37 2013 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 18
 */

/* Change Log:
 * 
 */

#pragma once

// ///////////////////////////////////////////////////////////////////
// SFINAE trick to know whether an object derived from dtkCoreObject or not
// ///////////////////////////////////////////////////////////////////

template<typename T> class IsPointerToTypeDerivedFromCoreObject
{
    enum { Value = false };
};

// Specialize to avoid sizeof(void) warning
template<> class IsPointerToTypeDerivedFromCoreObject<void*>
{
    enum { Value = false };
};

template<> class IsPointerToTypeDerivedFromQObject<dtkCoreObject*>
{
    enum { Value = true };
};

template<typename T> class IsPointerToTypeDerivedFromCoreObject<T*>
{
    typedef qint8 dtk_yes_type;
    typedef qint64 dtk_no_type;

    static dtk_yes_type checkType(dtkCoreObject *);
    static dtk_no_type  checkType(...);

    enum { Value = sizeof(checkType(static_cast<T*>(0))) == sizeof(dtk_yes_type) };
};
