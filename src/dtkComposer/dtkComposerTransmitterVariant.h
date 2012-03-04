/* dtkComposerTransmitterVariant.h --- 
 * 
 * Author: tkloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Fri Mar  2 16:19:20 2012 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Mar  4 22:40:37 2012 (+0100)
 *           By: tkloczko
 *     Update #: 50
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERTRANSMITTERVARIANT_H
#define DTKCOMPOSERTRANSMITTERVARIANT_H

#include "dtkComposerExport.h"
#include "dtkComposerTransmitter.h"

// /////////////////////////////////////////////////////////////////
// dtkComposerTransmitterVariant declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerTransmitterVariantPrivate;

class DTKCOMPOSER_EXPORT dtkComposerTransmitterVariant : public dtkComposerTransmitter
{
public:
     dtkComposerTransmitterVariant(QList<QVariant::Type> types, dtkComposerNode *parent = 0);
    ~dtkComposerTransmitterVariant(void);

public:
    void setData(const QBitArray& data);
    void setData(const QByteArray& data);
    void setData(const QChar& data);
    void setData(const char *data);
    void setData(const QString& data);
    void setData(const QStringList& data);
    void setData(const bool& data);
    void setData(const short& data);
    void setData(const int& data);
    void setData(const long& data);
    void setData(const qlonglong& data);
    void setData(const ushort& data);
    void setData(const uint& data);
    void setData(const ulong& data);
    void setData(const qulonglong& data);
    void setData(const float& data);
    void setData(const qreal& data);
    void setData(const QRegExp& data);
    void setData(const QUrl& data);

    void setData(void *data);

public:
    QBitArray   dataToBitArray(void);
    QByteArray  dataToByteArray(void);
    QChar       dataToChar(void);
    QString     dataToString(void);
    QStringList dataToStringList(void);
    bool        dataToBool(void);
    int         dataToInt(void);
    qlonglong   dataToLongLong(void);
    uint        dataToUInt(void);
    qulonglong  dataToULongLong(void);
    qreal       dataToReal(void);
    QRegExp     dataToRegExp(void);
    QUrl        dataToUrl(void);

public:
    Kind           kind(void) const;
    QVariant::Type type(void) const;

    QString kindName(void) const;
    QString typeName(void) const;
    
public:
          void *variant(void);
    const void *variant(void) const;

public:
    bool    connect(dtkComposerTransmitter *transmitter);
    bool disconnect(dtkComposerTransmitter *transmitter);

    LinkMap  leftLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list);
    LinkMap rightLinks(dtkComposerTransmitter *transmitter, dtkComposerTransmitterLinkList list);

private:
    dtkComposerTransmitterVariantPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// Helper functions
// /////////////////////////////////////////////////////////////////

template <typename T> QString        dtkComposerTransmitterVariantName(const T& t);
template <typename T> QVariant::Type dtkComposerTransmitterVariantType(const T& t);

// /////////////////////////////////////////////////////////////////

#include "dtkComposerTransmitterVariant.tpp"

#endif
