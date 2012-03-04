/* dtkComposerTransmitterVariant.tpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Sun Mar  4 15:43:44 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Mar  4 16:54:52 2012 (+0100)
 *           By: tkloczko
 *     Update #: 8
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERTRANSMITTERVARIANT_TPP
#define DTKCOMPOSERTRANSMITTERVARIANT_TPP

#include <typeinfo>

// /////////////////////////////////////////////////////////////////
// Related non-member templated functions
// /////////////////////////////////////////////////////////////////

template <typename T> QString dtkComposerTransmitterVariantName(const T& t)
{
    if (typeid(t) == typeid(QBitArray))
        return "QBitArray";
    if (typeid(t) == typeid(QByteArray))
        return "QByteArray";
    if (typeid(t) == typeid(QChar))
        return "QChar";
    if (typeid(t) == typeid(QString))
        return "QString";
    if (typeid(t) == typeid(QStringList))
        return "QStringList";
    if (typeid(t) == typeid(bool))
        return "Bool";
    if (typeid(t) == typeid(short))
        return "Integer";
    if (typeid(t) == typeid(int))
        return "Integer";
    if (typeid(t) == typeid(long))
        return "LongLong";
    if (typeid(t) == typeid(qlonglong))
        return "LongLong";
    if (typeid(t) == typeid(ushort))
        return "UInteger";
    if (typeid(t) == typeid(uint))
        return "UInteger";
    if (typeid(t) == typeid(ulong))
        return "ULongLong";
    if (typeid(t) == typeid(qulonglong))
        return "ULongLong";
    if (typeid(t) == typeid(float))
        return "Real";
    if (typeid(t) == typeid(qreal))
        return "Real";
    if (typeid(t) == typeid(QRegExp))
        return "QRegExp";
    if (typeid(t) == typeid(QUrl))
        return "QUrl";

    return typeid(t).name();
}

template <typename T> QVariant::Type dtkComposerTransmitterVariantType(const T& t)
{
    if (typeid(t) == typeid(QBitArray))
        return QVariant::BitArray;
    if (typeid(t) == typeid(QByteArray))
        return QVariant::ByteArray;
    if (typeid(t) == typeid(QChar))
        return QVariant::Char;
    if (typeid(t) == typeid(QString))
        return QVariant::String;
    if (typeid(t) == typeid(QStringList))
        return QVariant::StringList;
    if (typeid(t) == typeid(bool))
        return QVariant::Bool;
    if (typeid(t) == typeid(short))
        return QVariant::Int;
    if (typeid(t) == typeid(int))
        return QVariant::Int;
    if (typeid(t) == typeid(long))
        return QVariant::LongLong;
    if (typeid(t) == typeid(qlonglong))
        return QVariant::LongLong;
    if (typeid(t) == typeid(ushort))
        return QVariant::UInt;
    if (typeid(t) == typeid(uint))
        return QVariant::UInt;
    if (typeid(t) == typeid(ulong))
        return QVariant::ULongLong;
    if (typeid(t) == typeid(qulonglong))
        return QVariant::ULongLong;
    if (typeid(t) == typeid(float))
        return QVariant::Double;
    if (typeid(t) == typeid(qreal))
        return QVariant::Double;
    if (typeid(t) == typeid(QRegExp))
        return QVariant::RegExp;
    if (typeid(t) == typeid(QUrl))
        return QVariant::Url;

    return QVariant::Invalid;
}

#endif
