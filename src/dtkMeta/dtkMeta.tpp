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

template<typename T, bool B> inline bool dtkMetaTypeHandler<T, B>::canConvert(const QList<int>& types)
{
    bool can_convert = true;
    QVariant var = QVariant(qMetaTypeId<T>(reinterpret_cast<T *>(0)), 0);

    foreach(int i, types) {
        if (!var.canConvert(i)) {
            can_convert = false;
            break;
        }
    }

    return can_convert;
}

// /////////////////////////////////////////////////////////////////

template<typename T> inline bool dtkMetaTypeHandler<T *, false>::canConvert(const QList<int>& types)
{
    return dtkMetaTypeHandlerHelper<T *, std::is_abstract<T>::value>::canConvert(types);
}

template<typename T> inline QVariant dtkMetaTypeHandler<T *, false>::variantFromValue(T *t)
{
    return QVariant::fromValue(t);
}

template<typename T> inline T *dtkMetaTypeHandler<T *, false>::clone(T *t)
{
    return new T(*t);
}

// /////////////////////////////////////////////////////////////////

template<typename T> inline bool dtkMetaTypeHandler<T *, true>::canConvert(const QList<int>& types)
{
    return dtkMetaTypeHandlerHelper<T *, std::is_abstract<T>::value>::canConvert(types);
}

template<typename T> inline QVariant dtkMetaTypeHandler<T *, true>::variantFromValue(T *t)
{
    return QVariant(QMetaType::type(qPrintable(QString(t->metaObject()->className()) + "*")), &t, 1);
}

template<typename T> inline T *dtkMetaTypeHandler<T *, true>::clone(T *t)
{
    QString class_name(t->metaObject()->className());
    int class_type = QMetaType::type(qPrintable(class_name));

    if (class_type == QMetaType::UnknownType)
        return dtkMetaTypeHandlerHelper<T *, std::is_abstract<T>::value>::clone(t);

    return static_cast<T *>(QMetaType::create(class_type, t));
}

// /////////////////////////////////////////////////////////////////
// dtkMetaTypeHandlerHelper implementation
// /////////////////////////////////////////////////////////////////

template<typename T> inline bool dtkMetaTypeHandlerHelper<T *, false>::canConvert(const QList<int>& types)
{
    if ((types.size() == 1 && types.first() == qMetaTypeId<T *>()) || types.isEmpty())
        return true;

    bool can_convert = true;
    T *ptr = new T();
    QVariant var = QVariant::fromValue(ptr);

    foreach(int i, types) {
        if (!var.canConvert(i)) {
            can_convert = false;
            break;
        }
    }

    delete ptr;

    return can_convert;
}

template<typename T> inline T *dtkMetaTypeHandlerHelper<T *, false>::clone(T *t)
{
    return new T(*t);
}

template<typename T> inline bool dtkMetaTypeHandlerHelper<T *, true>::canConvert(const QList<int>& types)
{
    return ((types.size() == 1 && types.first() == qMetaTypeId<T *>()) || types.isEmpty());
}

template<typename T> inline T *dtkMetaTypeHandlerHelper<T *, true>::clone(T *t)
{
    Q_UNUSED(t);
    return NULL;
}

// /////////////////////////////////////////////////////////////////
// dtkMetaType implementation
// /////////////////////////////////////////////////////////////////

template<typename T> inline bool dtkMetaType::canConvert(int type)
{
    return dtkMetaType::canConvert<T>(QList<int>({type}));
}

template<typename T> inline bool dtkMetaType::canConvert(const QList<int>& types)
{
    return dtkMetaTypeHandler<T>::canConvert(types);
}

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
