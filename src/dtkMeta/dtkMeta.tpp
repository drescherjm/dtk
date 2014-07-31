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
// dtkMetaTypeHandler implementation
// /////////////////////////////////////////////////////////////////

template<typename T> inline QVariant dtkMetaTypeHandler<T *, false>::variantFromValue(T *t)
{
    return QVariant::fromValue(t);
}

template<typename T> inline T *dtkMetaTypeHandler<T *, false>::clone(T *t)
{
    return new T(*t);
}

template<typename T> inline QVariant dtkMetaTypeHandler<T *, true>::variantFromValue(T *t)
{
    return QVariant(QMetaType::type(qPrintable(QString(t->metaObject()->className()) + "*")), &t, 1);
}

template<typename T> inline T *dtkMetaTypeHandler<T *, true>::clone(T *t)
{
    return static_cast<T *>(QMetaType::create(QMetaType::type(qPrintable(QString(t->metaObject()->className()))), t));
}

// /////////////////////////////////////////////////////////////////
// dtkMetaType implementation
// /////////////////////////////////////////////////////////////////

template<typename T> inline QVariant dtkMetaType::variantFromValue(const T& t)
{
    return QVariant::fromValue(t);
}

template<typename T> inline QVariant dtkMetaType::variantFromValue(T *t)
{
    return dtkMetaTypeHandler<T *>::variantFromValue(t);
}

template<typename T> inline T *dtkMetaType::clone(T *t)
{
    return dtkMetaTypeHandler<T *>::clone(t);
}

// /////////////////////////////////////////////////////////////////
// Stream operators implementation
// /////////////////////////////////////////////////////////////////


template <typename T> inline QDataStream& operator << (QDataStream& s, T *t)
{
    s << *t;
    return s;
}

template <typename T> inline QDataStream& operator >> (QDataStream& s, T *& t)
{
    if (!t) {
        t = new T();
    }

    s >> *t;
    return s;
}

template<typename T> inline QDataStream& operator << (QDataStream& s, const QList<T *>& l)
{
    s << quint32(l.size());
    for (int i = 0; i < l.size(); ++i)
        s << dtkMetaType::variantFromValue(l.at(i));
    return s;
}

template<typename T> inline QDataStream& operator >> (QDataStream& s, const QList<T *>& l)
{
    l.clear();
    quint32 c; s >> c;
    for(quint32 i = 0; i < c; ++i) {
        QVariant var;
        s >> var;
        l << var.value<T *>();
        if (s.atEnd())
            break;
    }
    return s;
}

template<typename T> inline QDataStream& operator << (QDataStream& s, const QVector<T *>& v)
{
    s << quint32(v.size());
    for (typename QVector<T *>::const_iterator it = v.begin(); it != v.end(); ++it)
        s << dtkMetaType::variantFromValue(*it);
    return s;
}

template<typename T> inline QDataStream& operator >> (QDataStream& s, QVector<T *>& v)
{
    v.clear();
    quint32 c; s >> c;
    v.resize(c);
    for(quint32 i = 0; i < c; ++i) {
        QVariant var;
        s >> var;
        v[i] = var.value<T *>();
    }
    return s;
}

template<typename T> inline QDataStream& operator << (QDataStream& s, const std::list<T *>& l)
{
    s << quint32(l.size());
    for (typename std::list<T *>::const_iterator it = l.begin(); it != l.end(); ++it)
        s << dtkMetaType::variantFromValue(*it);
    return s;
}

template<typename T> inline QDataStream& operator >> (QDataStream& s, const std::list<T *>& l)
{
    l.clear();
    quint32 c; s >> c;
    for(quint32 i = 0; i < c; ++i) {
        QVariant var;
        s >> var;
        l.push_back(var.value<T *>());
        if (s.atEnd())
            break;
    }
    return s;
}

template<typename T> inline QDataStream& operator << (QDataStream& s, const std::vector<T *>& v)
{
    s << quint32(v.size());
    for (typename std::vector<T *>::const_iterator it = v.begin(); it != v.end(); ++it)
        s << dtkMetaType::variantFromValue(*it);
    return s;
}

template<typename T> inline QDataStream& operator >> (QDataStream& s, const std::vector<T *>& v)
{
    v.clear();
    quint32 c; s >> c;
    v.resize(c);
    for(quint32 i = 0; i < c; ++i) {
        QVariant var; // Very important to instantiate a void QVariant at each step, otherwise, it keeps the same pointer T* to store the stream.
        s >> var;
        v[i] = var.value<T *>();
    }
    return s;
}

//
// dtkMeta.tpp ends here
