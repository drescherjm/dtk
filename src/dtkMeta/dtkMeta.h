// Version: $Id$
//
//

// Commentary:
//
//

// Change Log:
//
//

// Code:

#pragma once

#include <QtCore>

// /////////////////////////////////////////////////////////////////
// dtkMetaTypeHandler definition
// /////////////////////////////////////////////////////////////////

template< typename T, bool = QtPrivate::IsPointerToTypeDerivedFromQObject<T>::Value > struct dtkMetaTypeHandler;

template<typename T> struct dtkMetaTypeHandler<T *, false>
{
    static QVariant  variantFromValue(T *t);
    static        T *clone(T *t);
};

template<typename T> struct dtkMetaTypeHandler<T *, true>
{
    static QVariant variantFromValue(T *t);
    static T *clone(T *t);
};

// /////////////////////////////////////////////////////////////////
// dtkMetaType definition
// /////////////////////////////////////////////////////////////////

class dtkMetaType
{
public:
                         static     bool canGetMetaContainerFromVariant(const QVariant& v);
    template<typename T> static QVariant variantFromValue(const T& t);
    template<typename T> static QVariant variantFromValue(      T *t);
    template<typename T> static        T *clone(T *t);
};

// /////////////////////////////////////////////////////////////////
// Stream operators redefinition
// /////////////////////////////////////////////////////////////////

template <typename T> QDataStream& operator << (QDataStream& s, T *  t);
template <typename T> QDataStream& operator >> (QDataStream& s, T *& t);

template<typename T> QDataStream& operator << (QDataStream& s, const QList<T *>& l);
template<typename T> QDataStream& operator >> (QDataStream& s,       QList<T *>& l);

template<typename T> QDataStream& operator << (QDataStream& s, const QVector<T *>& v);
template<typename T> QDataStream& operator >> (QDataStream& s,       QVector<T *>& v);

template<typename T> QDataStream& operator << (QDataStream& s, const std::list<T *>& l);
template<typename T> QDataStream& operator >> (QDataStream& s,       std::list<T *>& l);

template<typename T> QDataStream& operator << (QDataStream& s, const std::vector<T *>& v);
template<typename T> QDataStream& operator >> (QDataStream& s,       std::vector<T *>& v);

// /////////////////////////////////////////////////////////////////
// MACRO REGISTERING POINTERS OF CONTAINERS INTO METATYPE SYSTEM
// /////////////////////////////////////////////////////////////////

#define DTK_DECLARE_SEQUENTIAL_CONTAINER_POINTER(CONTAINER_ARG)                   \
QT_BEGIN_NAMESPACE                                                                \
template <typename T> struct QMetaTypeId< CONTAINER_ARG<T> *>                     \
{                                                                                 \
    enum {                                                                        \
        Defined = QMetaTypeId2<T>::Defined                                        \
    };                                                                            \
    static int qt_metatype_id()                                                   \
    {                                                                             \
        static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0);       \
        if (const int id = metatype_id.load())                                    \
            return id;                                                            \
        const char *tName = QMetaType::typeName(qMetaTypeId<T>());                \
        Q_ASSERT(tName);                                                          \
        const int tNameLen = int(qstrlen(tName));                                 \
        QByteArray typeName;                                                      \
        typeName.reserve(int(sizeof(#CONTAINER_ARG)) + 1 + tNameLen + 1 + 1 + 1); \
        typeName.append(#CONTAINER_ARG, int(sizeof(#CONTAINER_ARG)) - 1)          \
            .append('<').append(tName, tNameLen).append('*');                     \
        typeName.append('>');                                                     \
        const int newId = qRegisterNormalizedMetaType< CONTAINER_ARG<T> *>(       \
                        typeName,                                                 \
                        reinterpret_cast< CONTAINER_ARG<T> **>(quintptr(-1)));    \
        metatype_id.storeRelease(newId);                                          \
        return newId;                                                             \
    }                                                                             \
};                                                                                \
namespace QtPrivate {                                                             \
template<typename T> struct IsSequentialContainer<CONTAINER_ARG<T> *>             \
{                                                                                 \
    enum { Value = true };                                                        \
};                                                                                \
}                                                                                 \
QT_END_NAMESPACE

// /////////////////////////////////////////////////////////////////

#include "dtkMeta.tpp"

//
// dtkMeta.h ends here
