/* dtkComposerType.h ---
 * 
 * Author: Julien Wintz
 * Created: Wed Mar 20 12:46:40 2013 (+0100)
 * Version: 
 * Last-Updated: Wed Mar 20 13:08:31 2013 (+0100)
 *           By: Julien Wintz
 *     Update #: 4
 */

/* Change Log:
 * 
 */

#pragma once

#include <typeinfo>

typedef std::type_info dtkComposerType;

// /////////////////////////////////////////////////////////////////
// dtkComposerTypeInfoHandler interface (singleton)
// /////////////////////////////////////////////////////////////////

template <typename T> class dtkComposerTypeInfoHandler
{
public:
    static dtkComposerTypeInfoHandler<T>& instance(void);

public:
    const dtkComposerType    *type(void) { return &m_type; }
          QString typeName(void) { return m_type.name(); }    

private:
    dtkComposerTypeInfoHandler<T>(void) : m_type(typeid(T)) {}

private:
    static dtkComposerTypeInfoHandler<T> *s_instance;

private:
    const dtkComposerType& m_type;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTypeInfoHandler implementation
// /////////////////////////////////////////////////////////////////

template <typename T> dtkComposerTypeInfoHandler<T>& dtkComposerTypeInfoHandler<T>::instance(void)
{
    if (!s_instance)
        s_instance = new dtkComposerTypeInfoHandler<T>();

    return *s_instance;
}

template <typename T> dtkComposerTypeInfoHandler<T> *dtkComposerTypeInfoHandler<T>::s_instance = 0;

// /////////////////////////////////////////////////////////////////
// dtkComposerTypeInfoBase interface
// /////////////////////////////////////////////////////////////////

template <typename T> class dtkComposerTypeInfo
{
public:
    enum {
                isObjectPointer = false,
        isAbstractObjectPointer = false,
          isAbstractDataPointer = false,
            isMatrixRealPointer = false
    };

public:
    static const dtkComposerType    *type(void) { return dtkComposerTypeInfoHandler<T>::instance().type(); }
    static       QString typeName(void) { return dtkComposerTypeInfoHandler<T>::instance().typeName(); }
};

// /////////////////////////////////////////////////////////////////
// Full specialization for void*
// /////////////////////////////////////////////////////////////////

template <> class dtkComposerTypeInfo<void*>
{
public:
    enum {
                isObjectPointer = false,
        isAbstractObjectPointer = false,
          isAbstractDataPointer = false,
            isMatrixRealPointer = false
    };

public:
    static const dtkComposerType     *type(void) { return &const_cast<std::type_info&>(typeid(0)); }
    static       QString  typeName(void) { return "void*"; }
};

// /////////////////////////////////////////////////////////////////
// Helper functions to implement SFINAE
// /////////////////////////////////////////////////////////////////

typedef int  dtk_yes_type;
typedef char dtk_no_type;

class dtkAbstractObject;
class dtkAbstractData;
template <typename T> class dtkMatrix;

dtk_yes_type dtkComposerTypeInfoCheckObject(dtkAbstractObject*);
dtk_yes_type dtkComposerTypeInfoCheckObject(dtkMatrix<qreal>*);
dtk_no_type  dtkComposerTypeInfoCheckObject(...);

dtk_yes_type dtkComposerTypeInfoCheckAbstractObject(dtkAbstractObject*);
dtk_no_type  dtkComposerTypeInfoCheckAbstractObject(...);

dtk_yes_type dtkComposerTypeInfoCheckAbstractData(dtkAbstractData*);
dtk_no_type  dtkComposerTypeInfoCheckAbstractData(...);

dtk_yes_type dtkComposerTypeInfoCheckMatrix(dtkMatrix<qreal>*);
dtk_no_type  dtkComposerTypeInfoCheckMatrix(...);

// /////////////////////////////////////////////////////////////////
// dtkComposerTypeInfo partial specialization for pointer type
// /////////////////////////////////////////////////////////////////

template <typename T> class dtkComposerTypeInfo<T*>
{
public:
    enum { 
                isObjectPointer = (sizeof(dtkComposerTypeInfoCheckObject(static_cast<T*>(0))) == sizeof(dtk_yes_type)),
        isAbstractObjectPointer = (sizeof(dtkComposerTypeInfoCheckAbstractObject(static_cast<T*>(0))) == sizeof(dtk_yes_type)),
          isAbstractDataPointer = (sizeof(dtkComposerTypeInfoCheckAbstractData(static_cast<T*>(0))) == sizeof(dtk_yes_type)),
            isMatrixRealPointer = (sizeof(dtkComposerTypeInfoCheckMatrix(static_cast<T*>(0))) == sizeof(dtk_yes_type))
    };

public:
    static const dtkComposerType     *type(void) { return dtkComposerTypeInfoHandler<T*>::instance().type(); }
    static       QString  typeName(void) { return dtkComposerTypeInfoHandler<T*>::instance().typeName(); }
};
