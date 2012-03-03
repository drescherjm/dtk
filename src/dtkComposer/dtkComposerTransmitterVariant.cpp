/* dtkComposerTransmitterVariant.cpp --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Sat Mar  3 17:51:22 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Mar  4 00:18:01 2012 (+0100)
 *           By: tkloczko
 *     Update #: 164
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerTransmitterVariant.h"

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

    QVariant data;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterVariant implementation
// /////////////////////////////////////////////////////////////////



dtkComposerTransmitterVariant::dtkComposerTransmitterVariant(dtkComposerNode *parent) : dtkComposerTransmitter(parent), d(new dtkComposerTransmitterVariantPrivate)
{
    d->type = QVariant::Invalid; 
}

dtkComposerTransmitterVariant::~dtkComposerTransmitterVariant(void)
{
    delete d;

    d = NULL;
}

//! Returns.
/*! 
 *  
 */
QVariant::Type dtkComposerTransmitterVariant::variantType(void) const
{
    return d->type;
}

void dtkComposerTransmitterVariant::setData(const QBitArray& data)
{
    d->bit_array = data;
    d->type = QVariant::BitArray;
}

void dtkComposerTransmitterVariant::setData(const QByteArray& data)
{
    d->byte_array = data;
    d->type = QVariant::ByteArray;
}

void dtkComposerTransmitterVariant::setData(const QChar& data)
{
    d->char_array = data;
    d->type = QVariant::Char;
}

void dtkComposerTransmitterVariant::setData(const char *data)
{
    d->string = QString::fromAscii(data);
    d->type = QVariant::String;
}

void dtkComposerTransmitterVariant::setData(const QString& data)
{
    d->string = data;
    d->type = QVariant::String;
}

void dtkComposerTransmitterVariant::setData(const QStringList& data)
{
    d->string_list = data;
    d->type = QVariant::StringList;
}

void dtkComposerTransmitterVariant::setData(const bool& data)
{
    d->b = data;
    d->type = QVariant::Bool;
}

void dtkComposerTransmitterVariant::setData(const short& data)
{
    d->i = (int)data;
    d->type = QVariant::Int;
}

void dtkComposerTransmitterVariant::setData(const int& data)
{
    d->i = data;
    d->type = QVariant::Int;
}

void dtkComposerTransmitterVariant::setData(const long& data)
{
    d->ll = (qlonglong)data;
    d->type = QVariant::LongLong;
}

void dtkComposerTransmitterVariant::setData(const qlonglong& data)
{
    d->ll = data;
    d->type = QVariant::LongLong;
}

void dtkComposerTransmitterVariant::setData(const ushort& data)
{
    d->ui = (uint)data;
    d->type = QVariant::UInt;
}

void dtkComposerTransmitterVariant::setData(const uint& data)
{
    d->ui = data;
    d->type = QVariant::UInt;
}

void dtkComposerTransmitterVariant::setData(const ulong& data)
{
    d->ull = (qulonglong)data;
    d->type = QVariant::ULongLong;
}

void dtkComposerTransmitterVariant::setData(const qulonglong& data)
{
    d->ull = data;
    d->type = QVariant::ULongLong;
}

void dtkComposerTransmitterVariant::setData(const float& data)
{
    d->real = (qreal)data;
    d->type = QVariant::Double;
}

void dtkComposerTransmitterVariant::setData(const qreal& data)
{
    d->real = data;
    d->type = QVariant::Double;
}

void dtkComposerTransmitterVariant::setData(const QRegExp& data)
{
    d->reg_exp = data;
    d->type = QVariant::RegExp;
}

void dtkComposerTransmitterVariant::setData(const QUrl& data)
{
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
        d->data = QVariant(d->type);
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
    // if (transmitter->typeName())

    // if (d->type == QVariant::Invalid) {

    //     if ()


    // }

    return false;
}

//! 
/*! 
 *  
 */
bool dtkComposerTransmitterVariant::disconnect(dtkComposerTransmitter *transmitter)
{

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

QVariant::Type dtkComposerTransmitterVariant::typeNameToVariantType(const char *type_name)
{
    if (strcmp(type_name, "QBitArray") == 0)
        return QVariant::BitArray;
    if (strcmp(type_name, typeid(QByteArray).name()) == 0)
        return QVariant::ByteArray;
    if (strcmp(type_name, typeid(QChar).name()) == 0)
        return QVariant::Char;
    if (strcmp(type_name, typeid(QString).name()) == 0)
        return QVariant::String;
    if (strcmp(type_name, typeid(QStringList).name()) == 0)
        return QVariant::StringList;
    if (strcmp(type_name, typeid(bool).name()) == 0)
        return QVariant::Bool;
    if (strcmp(type_name, typeid(short).name()) == 0)
        return QVariant::Int;
    if (strcmp(type_name, typeid(int).name()) == 0)
        return QVariant::Int;
    if (strcmp(type_name, typeid(long).name()) == 0)
        return QVariant::LongLong;
    if (strcmp(type_name, typeid(qlonglong).name()) == 0)
        return QVariant::LongLong;
    if (strcmp(type_name, typeid(ushort).name()) == 0)
        return QVariant::UInt;
    if (strcmp(type_name, typeid(uint).name()) == 0)
        return QVariant::UInt;
    if (strcmp(type_name, typeid(ulong).name()) == 0)
        return QVariant::ULongLong;
    if (strcmp(type_name, typeid(qulonglong).name()) == 0)
        return QVariant::ULongLong;
    if (strcmp(type_name, typeid(float).name()) == 0)
        return QVariant::Double;
    if (strcmp(type_name, typeid(qreal).name()) == 0)
        return QVariant::Double;
    if (strcmp(type_name, typeid(QRegExp).name()) == 0)
        return QVariant::RegExp;
    if (strcmp(type_name, typeid(QUrl).name()) == 0)
        return QVariant::Url;

    return QVariant::Invalid;
}

QString dtkComposerTransmitterVariant::typeNameToVariantName(const char *type_name)
{
    if (strcmp(type_name, typeid(QBitArray).name()) == 0)
        return "QBitArray";
    if (strcmp(type_name, typeid(QByteArray).name()) == 0)
        return "QByteArray";
    if (strcmp(type_name, typeid(QChar).name()) == 0)
        return "QChar";
    if (strcmp(type_name, typeid(QString).name()) == 0)
        return "QString";
    if (strcmp(type_name, typeid(QStringList).name()) == 0)
        return "QStringList";
    if (strcmp(type_name, typeid(bool).name()) == 0)
        return "bool";
    if (strcmp(type_name, typeid(short).name()) == 0)
        return "int";
    if (strcmp(type_name, typeid(int).name()) == 0)
        return "int";
    if (strcmp(type_name, typeid(long).name()) == 0)
        return "longlong";
    if (strcmp(type_name, typeid(qlonglong).name()) == 0)
        return "longlong";
    if (strcmp(type_name, typeid(ushort).name()) == 0)
        return "uint";
    if (strcmp(type_name, typeid(uint).name()) == 0)
        return "uint";
    if (strcmp(type_name, typeid(ulong).name()) == 0)
        return "ulonglong";
    if (strcmp(type_name, typeid(qulonglong).name()) == 0)
        return "ulonglong";
    if (strcmp(type_name, typeid(float).name()) == 0)
        return "double";
    if (strcmp(type_name, typeid(qreal).name()) == 0)
        return "double";
    if (strcmp(type_name, typeid(QRegExp).name()) == 0)
        return "QRegExp";
    if (strcmp(type_name, typeid(QUrl).name()) == 0)
        return "QUrl";

    return type_name;
}
