/* dtkComposerTransmitterVariant.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Sat Mar  3 17:51:22 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Mar  4 22:47:08 2012 (+0100)
 *           By: tkloczko
 *     Update #: 239
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerTransmitterVariant.h"

#include <dtkCore/dtkGlobal.h>

#include <typeinfo>

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterVariantPrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerTransmitterVariantPrivate
{
public:
    QList<dtkComposerTransmitter *> emitters;

public:
    QBitArray   bit_array;
    QByteArray  byte_array;
    QChar       char_array;
    QString     string;
    QStringList string_list;
    bool        b;
    int         i;
    qlonglong   ll;
    uint        ui;
    qulonglong  ull;
    qreal       real;
    QRegExp     reg_exp;
    QUrl        url;

public:
    QVariant::Type type;

public:
    QList<QVariant::Type> types;

public:
    int count_ref;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterVariant implementation
// /////////////////////////////////////////////////////////////////

dtkComposerTransmitterVariant::dtkComposerTransmitterVariant(QList<QVariant::Type> types, dtkComposerNode *parent) : dtkComposerTransmitter(parent), d(new dtkComposerTransmitterVariantPrivate)
{
    d->count_ref = 0;
    d->types = types;
    d->type  = QVariant::Invalid; 
}

dtkComposerTransmitterVariant::~dtkComposerTransmitterVariant(void)
{
    delete d;

    d = NULL;
}

void dtkComposerTransmitterVariant::setData(const QBitArray& data)
{
    if (!d->types.contains(QVariant::BitArray)) {
        qDebug() << DTK_PRETTY_FUNCTION << "BitArray type is not handled.";
        return;
    }

    d->bit_array = data;
    d->type = QVariant::BitArray;
}

void dtkComposerTransmitterVariant::setData(const QByteArray& data)
{
    if (!d->types.contains(QVariant::ByteArray)) {
        qDebug() << DTK_PRETTY_FUNCTION << "ByteArray type is not handled.";
        return;
    }

    d->byte_array = data;
    d->type = QVariant::ByteArray;
}

void dtkComposerTransmitterVariant::setData(const QChar& data)
{
    if (!d->types.contains(QVariant::Char)) {
        qDebug() << DTK_PRETTY_FUNCTION << "Char type is not handled.";
        return;
    }

    d->char_array = data;
    d->type = QVariant::Char;
}

void dtkComposerTransmitterVariant::setData(const char *data)
{
    if (!d->types.contains(QVariant::String)) {
        qDebug() << DTK_PRETTY_FUNCTION << "String type is not handled.";
        return;
    }

    d->string = QString::fromAscii(data);
    d->type = QVariant::String;
}

void dtkComposerTransmitterVariant::setData(const QString& data)
{
    if (!d->types.contains(QVariant::String)) {
        qDebug() << DTK_PRETTY_FUNCTION << "String type is not handled.";
        return;
    }

    d->string = data;
    d->type = QVariant::String;
}

void dtkComposerTransmitterVariant::setData(const QStringList& data)
{
    if (!d->types.contains(QVariant::StringList)) {
        qDebug() << DTK_PRETTY_FUNCTION << "StringList type is not handled.";
        return;
    }

    d->string_list = data;
    d->type = QVariant::StringList;
}

void dtkComposerTransmitterVariant::setData(const bool& data)
{
    if (!d->types.contains(QVariant::Bool)) {
        qDebug() << DTK_PRETTY_FUNCTION << "Bool type is not handled.";
        return;
    }

    d->b = data;
    d->type = QVariant::Bool;
}

void dtkComposerTransmitterVariant::setData(const short& data)
{
    if (!d->types.contains(QVariant::Int)) {
        qDebug() << DTK_PRETTY_FUNCTION << "Int type is not handled.";
        return;
    }

    d->i = (int)data;
    d->type = QVariant::Int;
}

void dtkComposerTransmitterVariant::setData(const int& data)
{
    if (!d->types.contains(QVariant::Int)) {
        qDebug() << DTK_PRETTY_FUNCTION << "Int type is not handled.";
        return;
    }

    d->i = data;
    d->type = QVariant::Int;
}

void dtkComposerTransmitterVariant::setData(const long& data)
{
    if (!d->types.contains(QVariant::LongLong)) {
        qDebug() << DTK_PRETTY_FUNCTION << "LongLong type is not handled.";
        return;
    }

    d->ll = (qlonglong)data;
    d->type = QVariant::LongLong;
}

void dtkComposerTransmitterVariant::setData(const qlonglong& data)
{
    if (!d->types.contains(QVariant::LongLong)) {
        qDebug() << DTK_PRETTY_FUNCTION << "LongLong type is not handled.";
        return;
    }

    d->ll = data;
    d->type = QVariant::LongLong;
}

void dtkComposerTransmitterVariant::setData(const ushort& data)
{
    if (!d->types.contains(QVariant::UInt)) {
        qDebug() << DTK_PRETTY_FUNCTION << "UInt type is not handled.";
        return;
    }

    d->ui = (uint)data;
    d->type = QVariant::UInt;
}

void dtkComposerTransmitterVariant::setData(const uint& data)
{
    if (!d->types.contains(QVariant::UInt)) {
        qDebug() << DTK_PRETTY_FUNCTION << "UInt type is not handled.";
        return;
    }

    d->ui = data;
    d->type = QVariant::UInt;
}

void dtkComposerTransmitterVariant::setData(const ulong& data)
{
    if (!d->types.contains(QVariant::ULongLong)) {
        qDebug() << DTK_PRETTY_FUNCTION << "ULongLong type is not handled.";
        return;
    }

    d->ull = (qulonglong)data;
    d->type = QVariant::ULongLong;
}

void dtkComposerTransmitterVariant::setData(const qulonglong& data)
{
    if (!d->types.contains(QVariant::ULongLong)) {
        qDebug() << DTK_PRETTY_FUNCTION << "ULongLong type is not handled.";
        return;
    }

    d->ull = data;
    d->type = QVariant::ULongLong;
}

void dtkComposerTransmitterVariant::setData(const float& data)
{
    if (!d->types.contains(QVariant::Double)) {
        qDebug() << DTK_PRETTY_FUNCTION << "Double type is not handled.";
        return;
    }

    d->real = (qreal)data;
    d->type = QVariant::Double;
}

void dtkComposerTransmitterVariant::setData(const qreal& data)
{
    if (!d->types.contains(QVariant::Double)) {
        qDebug() << DTK_PRETTY_FUNCTION << "Double type is not handled.";
        return;
    }

    d->real = data;
    d->type = QVariant::Double;
}

void dtkComposerTransmitterVariant::setData(const QRegExp& data)
{
    if (!d->types.contains(QVariant::RegExp)) {
        qDebug() << DTK_PRETTY_FUNCTION << "RegExp type is not handled.";
        return;
    }

    d->reg_exp = data;
    d->type = QVariant::RegExp;
}

void dtkComposerTransmitterVariant::setData(const QUrl& data)
{
    if (!d->types.contains(QVariant::Url)) {
        qDebug() << DTK_PRETTY_FUNCTION << "Url type is not handled.";
        return;
    }

    d->url = data;
    d->type = QVariant::Url;
}

void dtkComposerTransmitterVariant::setData(void *data)
{
    switch(d->type) {
    case QVariant::BitArray:
        d->bit_array = *(reinterpret_cast<QBitArray *>(data));
        break;
    case QVariant::ByteArray:
        d->byte_array = *(reinterpret_cast<QByteArray *>(data));
        break;
    case QVariant::Char:
        d->char_array = *(reinterpret_cast<QChar *>(data));
        break;
    case QVariant::String:
        d->string = *(reinterpret_cast<QString *>(data));
        break;
    case QVariant::StringList:
        d->string_list = *(reinterpret_cast<QStringList *>(data));
        break;
    case QVariant::Bool:
        d->b = *(reinterpret_cast<bool *>(data));
        break;
    case QVariant::Int:
        d->i = *(reinterpret_cast<int *>(data));
        break;
    case QVariant::LongLong:
        d->ll = *(reinterpret_cast<qlonglong *>(data));
        break;
    case QVariant::UInt:
        d->ui = *(reinterpret_cast<uint *>(data));
        break;
    case QVariant::ULongLong:
        d->ull = *(reinterpret_cast<qulonglong *>(data));
        break;
    case QVariant::Double:
        d->real = *(reinterpret_cast<qreal *>(data));
        break;
    case QVariant::RegExp:
        d->reg_exp = *(reinterpret_cast<QRegExp *>(data));
        break;
    case QVariant::Url:
        d->url = *(reinterpret_cast<QUrl *>(data));
        break;
    case QVariant::Invalid:
        break;
    };
}

QBitArray dtkComposerTransmitterVariant::dataToBitArray(void)
{
    if (d->type == QVariant::BitArray) {    
        foreach(dtkComposerTransmitter *e, d->emitters) {
            if (e->active())
                return *(static_cast<QBitArray *>(e->variant()));
        }
    }

    return QBitArray();
}

QByteArray dtkComposerTransmitterVariant::dataToByteArray(void)
{
    if (d->type == QVariant::ByteArray) {
        foreach(dtkComposerTransmitter *e, d->emitters) {
            if (e->active())
                return *(static_cast<QByteArray *>(e->variant()));
        }
    }

    if (d->type == QVariant::String) {
        foreach(dtkComposerTransmitter *e, d->emitters) {
            if (e->active())
                return (*(static_cast<QString *>(e->variant()))).toAscii();
        }
    }

    return QByteArray();
}

QChar dtkComposerTransmitterVariant::dataToChar(void)
{
    if (d->type == QVariant::Char) {
        foreach(dtkComposerTransmitter *e, d->emitters) {
            if (e->active())
                return *(static_cast<QChar *>(e->variant()));
        }
    }

    if (d->type == QVariant::Int) {
        foreach(dtkComposerTransmitter *e, d->emitters) {
            if (e->active())
                return QChar(*(static_cast<int *>(e->variant())));
        }
    }

    if (d->type == QVariant::UInt) {
        foreach(dtkComposerTransmitter *e, d->emitters) {
            if (e->active())
                return QChar(*(static_cast<uint *>(e->variant())));
        }
    }

    return QChar();
}

QString dtkComposerTransmitterVariant::dataToString(void)
{
    if (d->type == QVariant::String) {
        foreach(dtkComposerTransmitter *e, d->emitters) {
            if (e->active())
                return *(static_cast<QString *>(e->variant()));
        }
    }

    if (d->type == QVariant::ByteArray) {
        foreach(dtkComposerTransmitter *e, d->emitters) {
            if (e->active())
                return (*(static_cast<QByteArray *>(e->variant()))).data();
        }
    }

    if (d->type == QVariant::Char) {
        foreach(dtkComposerTransmitter *e, d->emitters) {
            if (e->active())
                return QString((*(static_cast<QChar *>(e->variant()))));
        }
    }

    if (d->type == QVariant::Bool) {
        foreach(dtkComposerTransmitter *e, d->emitters) {
            if (e->active())
                return QString::number(*(reinterpret_cast<int *>(e->variant())));
        }
    }

    if (d->type == QVariant::Int) {
        foreach(dtkComposerTransmitter *e, d->emitters) {
            if (e->active())
                return QString::number(*(static_cast<int *>(e->variant())));
        }
    }

    if (d->type == QVariant::UInt) {
        foreach(dtkComposerTransmitter *e, d->emitters) {
            if (e->active())
                return QString::number(*(static_cast<uint *>(e->variant())));
        }
    }

    if (d->type == QVariant::LongLong) {
        foreach(dtkComposerTransmitter *e, d->emitters) {
            if (e->active())
                return QString::number(*(static_cast<qlonglong *>(e->variant())));
        }
    }

    if (d->type == QVariant::ULongLong) {
        foreach(dtkComposerTransmitter *e, d->emitters) {
            if (e->active())
                return QString::number(*(static_cast<qulonglong *>(e->variant())));
        }
    }

    if (d->type == QVariant::Double) {
        foreach(dtkComposerTransmitter *e, d->emitters) {
            if (e->active())
                return QString::number(*(static_cast<qreal *>(e->variant())));
        }
    }

    return QString();
}

QStringList dtkComposerTransmitterVariant::dataToStringList(void)
{
    if (d->type == QVariant::StringList) {
        foreach(dtkComposerTransmitter *e, d->emitters) {
            if (e->active())
                return *(static_cast<QStringList *>(e->variant()));
        }
    }

    if (d->type == QVariant::String) {
        foreach(dtkComposerTransmitter *e, d->emitters) {
            if (e->active())
                return QStringList(*(static_cast<QStringList *>(e->variant())));
        }
    }

    return QStringList();
}

bool dtkComposerTransmitterVariant::dataToBool(void)
{
    if (d->type == QVariant::Bool) {
        foreach(dtkComposerTransmitter *e, d->emitters) {
            if (e->active())
                return *(static_cast<bool *>(e->variant()));
        }
    }

    if (d->type == QVariant::Int       || 
        d->type == QVariant::UInt      ||
        d->type == QVariant::LongLong  ||
        d->type == QVariant::ULongLong ||
        d->type == QVariant::Double) {
        foreach(dtkComposerTransmitter *e, d->emitters) {
            if (e->active())
                return *(reinterpret_cast<bool *>(e->variant()));
        }
    }

    if (d->type == QVariant::Char) {
        foreach(dtkComposerTransmitter *e, d->emitters) {
            if (e->active())
                return (*(static_cast<QChar *>(e->variant()))).toAscii();
        }
    }

    if (d->type == QVariant::String) {
        foreach(dtkComposerTransmitter *e, d->emitters) {
            if (e->active())
                return (*(static_cast<QString *>(e->variant()))).isEmpty();
        }
    }

    if (d->type == QVariant::ByteArray) {
        foreach(dtkComposerTransmitter *e, d->emitters) {
            if (e->active())
                return (*(static_cast<QByteArray *>(e->variant()))).isEmpty();
        }
    }

    return false;
}

int dtkComposerTransmitterVariant::dataToInt(void)
{
    if (d->type == QVariant::Int) {
        foreach(dtkComposerTransmitter *e, d->emitters) {
            if (e->active())
                return *(static_cast<int *>(e->variant()));
        }
    }

    if (d->type == QVariant::Bool      || 
        d->type == QVariant::UInt      ||
        d->type == QVariant::LongLong  ||
        d->type == QVariant::ULongLong ||
        d->type == QVariant::Double) {
        foreach(dtkComposerTransmitter *e, d->emitters) {
            if (e->active())
                return *(static_cast<int *>(e->variant()));
        }
    }

    if (d->type == QVariant::Char) {
        foreach(dtkComposerTransmitter *e, d->emitters) {
            if (e->active())
                return (*(static_cast<QChar *>(e->variant()))).toAscii();
        }
    }

    if (d->type == QVariant::String) {
        foreach(dtkComposerTransmitter *e, d->emitters) {
            if (e->active())
                return (*(static_cast<QString *>(e->variant()))).toInt();
        }
    }

    if (d->type == QVariant::ByteArray) {
        foreach(dtkComposerTransmitter *e, d->emitters) {
            if (e->active())
                return (*(static_cast<QByteArray *>(e->variant()))).toInt();
        }
    }

    return 0;
}

qlonglong dtkComposerTransmitterVariant::dataToLongLong(void)
{
    if (d->type == QVariant::LongLong) {
        foreach(dtkComposerTransmitter *e, d->emitters) {
            if (e->active())
                return *(static_cast<qlonglong *>(e->variant()));
        }
    }

    if (d->type == QVariant::Bool      || 
        d->type == QVariant::Int       ||
        d->type == QVariant::UInt      ||
        d->type == QVariant::ULongLong ||
        d->type == QVariant::Double) {
        foreach(dtkComposerTransmitter *e, d->emitters) {
            if (e->active())
                return *(reinterpret_cast<qlonglong *>(e->variant()));
        }
    }

    if (d->type == QVariant::Char) {
        foreach(dtkComposerTransmitter *e, d->emitters) {
            if (e->active())
                return (*(static_cast<QChar *>(e->variant()))).toAscii();
        }
    }

    if (d->type == QVariant::String) {
        foreach(dtkComposerTransmitter *e, d->emitters) {
            if (e->active())
                return (*(static_cast<QString *>(e->variant()))).toLongLong();
        }
    }

    if (d->type == QVariant::ByteArray) {
        foreach(dtkComposerTransmitter *e, d->emitters) {
            if (e->active())
                return (*(static_cast<QByteArray *>(e->variant()))).toLongLong();
        }
    }

    return 0;
}

uint dtkComposerTransmitterVariant::dataToUInt(void)
{
    if (d->type == QVariant::UInt) {
        foreach(dtkComposerTransmitter *e, d->emitters) {
            if (e->active())
                return *(static_cast<uint *>(e->variant()));
        }
    }

    if (d->type == QVariant::Bool      || 
        d->type == QVariant::Int       ||
        d->type == QVariant::LongLong  ||
        d->type == QVariant::ULongLong ||
        d->type == QVariant::Double) {
        foreach(dtkComposerTransmitter *e, d->emitters) {
            if (e->active())
                return *(static_cast<uint *>(e->variant()));
        }
    }

    if (d->type == QVariant::Char) {
        foreach(dtkComposerTransmitter *e, d->emitters) {
            if (e->active())
                return (*(static_cast<QChar *>(e->variant()))).toAscii();
        }
    }

    if (d->type == QVariant::String) {
        foreach(dtkComposerTransmitter *e, d->emitters) {
            if (e->active())
                return (*(static_cast<QString *>(e->variant()))).toUInt();
        }
    }

    if (d->type == QVariant::ByteArray) {
        foreach(dtkComposerTransmitter *e, d->emitters) {
            if (e->active())
                return (*(static_cast<QByteArray *>(e->variant()))).toUInt();
        }
    }

    return 0;
}

qulonglong dtkComposerTransmitterVariant::dataToULongLong(void)
{
    if (d->type == QVariant::ULongLong) {
        foreach(dtkComposerTransmitter *e, d->emitters) {
            if (e->active())
                return *(static_cast<qulonglong *>(e->variant()));
        }
    }

    if (d->type == QVariant::Bool     || 
        d->type == QVariant::Int      ||
        d->type == QVariant::UInt     ||
        d->type == QVariant::LongLong ||
        d->type == QVariant::Double) {
        foreach(dtkComposerTransmitter *e, d->emitters) {
            if (e->active())
                return *(static_cast<qulonglong *>(e->variant()));
        }
    }

    if (d->type == QVariant::Char) {
        foreach(dtkComposerTransmitter *e, d->emitters) {
            if (e->active())
                return (*(static_cast<QChar *>(e->variant()))).toAscii();
        }
    }

    if (d->type == QVariant::String) {
        foreach(dtkComposerTransmitter *e, d->emitters) {
            if (e->active())
                return (*(static_cast<QString *>(e->variant()))).toULongLong();
        }
    }

    if (d->type == QVariant::ByteArray) {
        foreach(dtkComposerTransmitter *e, d->emitters) {
            if (e->active())
                return (*(static_cast<QByteArray *>(e->variant()))).toULongLong();
        }
    }

    return 0;
}

qreal dtkComposerTransmitterVariant::dataToReal(void)
{
    if (d->type == QVariant::Double) {
        foreach(dtkComposerTransmitter *e, d->emitters) {
            if (e->active())
                return *(static_cast<qreal *>(e->variant()));
        }
    }

    if (d->type == QVariant::Bool     || 
        d->type == QVariant::Int      ||
        d->type == QVariant::UInt     ||
        d->type == QVariant::LongLong ||
        d->type == QVariant::Double) {
        foreach(dtkComposerTransmitter *e, d->emitters) {
            if (e->active())
                return *(reinterpret_cast<qreal *>(e->variant()));
        }
    }

    if (d->type == QVariant::Char) {
        foreach(dtkComposerTransmitter *e, d->emitters) {
            if (e->active())
                return (*(static_cast<QChar *>(e->variant()))).toAscii();
        }
    }

    if (d->type == QVariant::String) {
        foreach(dtkComposerTransmitter *e, d->emitters) {
            if (e->active())
                return (*(static_cast<QString *>(e->variant()))).toDouble();
        }
    }

    if (d->type == QVariant::ByteArray) {
        foreach(dtkComposerTransmitter *e, d->emitters) {
            if (e->active())
                return (*(static_cast<QByteArray *>(e->variant()))).toDouble();
        }
    }

    return 0.0;
}

QRegExp dtkComposerTransmitterVariant::dataToRegExp(void)
{
    if (d->type == QVariant::RegExp) {
        foreach(dtkComposerTransmitter *e, d->emitters) {
            if (e->active())
                return *(static_cast<QRegExp *>(e->variant()));
        }
    }

    return QRegExp();
} 
   

QUrl dtkComposerTransmitterVariant::dataToUrl(void)
{
    if (d->type == QVariant::Url) {
        foreach(dtkComposerTransmitter *e, d->emitters) {
            if (e->active())
                return *(static_cast<QUrl *>(e->variant()));
        }
    }

    return QUrl();
}

//! Returns.
/*! 
 *  
 */
dtkComposerTransmitter::Kind dtkComposerTransmitterVariant::kind(void) const
{
    return dtkComposerTransmitter::Variant;
}

//! Returns.
/*! 
 *  
 */
QVariant::Type dtkComposerTransmitterVariant::type(void) const
{
    return d->type;
}

QString dtkComposerTransmitterVariant::kindName(void) const
{
    return "Variant";
}

QString dtkComposerTransmitterVariant::typeName(void) const
{
    return QVariant::typeToName(d->type);
}

//! Returns
/*! 
 *  
 */
void *dtkComposerTransmitterVariant::variant(void)
{
    switch(d->type) {
    case QVariant::BitArray:
        return static_cast<void *>(&(d->bit_array));
        break;
    case QVariant::ByteArray:
        return static_cast<void *>(&(d->byte_array));
        break;
    case QVariant::Char:
        return static_cast<void *>(&(d->char_array));
        break;
    case QVariant::String:
        return static_cast<void *>(&(d->string));
        break;
    case QVariant::StringList:
        return static_cast<void *>(&(d->string_list));
        break;
    case QVariant::Bool:
        return static_cast<void *>(&(d->b));
        break;
    case QVariant::Int:
        return static_cast<void *>(&(d->i));
        break;
    case QVariant::LongLong:
        return static_cast<void *>(&(d->ll));
        break;
    case QVariant::UInt:
        return static_cast<void *>(&(d->ui));
        break;
    case QVariant::ULongLong:
        return static_cast<void *>(&(d->ull));
        break;
    case QVariant::Double:
        return static_cast<void *>(&(d->real));
        break;
    case QVariant::RegExp:
        return static_cast<void *>(&(d->reg_exp));
        break;
    case QVariant::Url:
        return static_cast<void *>(&(d->url));
        break;
    case QVariant::Invalid:
        return static_cast<void *>(NULL);
        break;
    };

    return static_cast<void *>(NULL);
}

//! Returns
/*! 
 *  
 */
const void *dtkComposerTransmitterVariant::variant(void) const
{
    switch(d->type) {
    case QVariant::BitArray:
        return static_cast<const void *>(&(d->bit_array));
        break;
    case QVariant::ByteArray:
        return static_cast<const void *>(&(d->byte_array));
        break;
    case QVariant::Char:
        return static_cast<const void *>(&(d->char_array));
        break;
    case QVariant::String:
        return static_cast<const void *>(&(d->string));
        break;
    case QVariant::StringList:
        return static_cast<const void *>(&(d->string_list));
        break;
    case QVariant::Bool:
        return static_cast<const void *>(&(d->b));
        break;
    case QVariant::Int:
        return static_cast<const void *>(&(d->i));
        break;
    case QVariant::LongLong:
        return static_cast<const void *>(&(d->ll));
        break;
    case QVariant::UInt:
        return static_cast<const void *>(&(d->ui));
        break;
    case QVariant::ULongLong:
        return static_cast<const void *>(&(d->ull));
        break;
    case QVariant::Double:
        return static_cast<const void *>(&(d->real));
        break;
    case QVariant::RegExp:
        return static_cast<const void *>(&(d->reg_exp));
        break;
    case QVariant::Url:
        return static_cast<const void *>(&(d->url));
        break;
    case QVariant::Invalid:
        return static_cast<const void *>(NULL);
        break;
    };

    return static_cast<const void *>(NULL);    
}

//! 
/*! 
 *  
 */
bool dtkComposerTransmitterVariant::connect(dtkComposerTransmitter *transmitter)
{
    if (d->count_ref == 0) {
        if (d->types.contains(transmitter->type())) {
            d->type = transmitter->type();
            d->emitters << transmitter;
            d->count_ref++;
            return true;
        }
    }

    if (transmitter->type() == d->type) {
        if (!d->emitters.contains(transmitter)) {
            d->emitters << transmitter;
            d->count_ref++;
            return true;
        }
    }

    if (d->types.contains(transmitter->type())) {
        if (!d->emitters.contains(transmitter)) {
            d->emitters << transmitter;
            return true;
        }
    }

    return false;
}

//! 
/*! 
 *  
 */
bool dtkComposerTransmitterVariant::disconnect(dtkComposerTransmitter *transmitter)
{
    if (transmitter->type() == d->type) {
        if (d->emitters.removeOne(transmitter)) {
            if (transmitter->type() == d->type)
                d->count_ref--;
            if (d->count_ref == 0 && d->emitters.count() > 0) {
                d->type = d->emitters.first()->type();
                foreach(dtkComposerTransmitter *t, d->emitters)
                    if (t->type() == d->type)
                        d->count_ref++;
            }
            return true;
        }
    }

    return false;
}

dtkComposerTransmitter::LinkMap dtkComposerTransmitterVariant::leftLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list)
{
    LinkMap link_map;
    foreach(dtkComposerTransmitterLink *l, list)
        link_map.insert(this, l);

    return link_map;
}

dtkComposerTransmitter::LinkMap dtkComposerTransmitterVariant::rightLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list)
{
    LinkMap link_map;
    foreach(dtkComposerTransmitterLink *l, list)
        link_map.insert(this, l);

    return link_map;
}
