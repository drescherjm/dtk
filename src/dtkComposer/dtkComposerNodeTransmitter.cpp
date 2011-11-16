/* dtkComposerNodeTransmitter.cpp --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Nov  2 11:04:35 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Nov 15 16:42:21 2011 (+0100)
 *           By: Thibaud Kloczko
 *     Update #: 17
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkComposerNodeTransmitter.h"

#include <QtCore/QDebug>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeAbstractTransmitterPrivate declaration
// /////////////////////////////////////////////////////////////////

class dtkComposerNodeAbstractTransmitterPrivate
{
public:
    QHash<QString, QStringList> metadatas;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeAbstractTransmitter implementation
// /////////////////////////////////////////////////////////////////

dtkComposerNodeAbstractTransmitter::dtkComposerNodeAbstractTransmitter(void) : d(new dtkComposerNodeAbstractTransmitterPrivate)
{

}

dtkComposerNodeAbstractTransmitter::~dtkComposerNodeAbstractTransmitter(void)
{
    delete d;
    d = NULL;
}

void dtkComposerNodeAbstractTransmitter::addMetaData(const QString& key, const QStringList& values)
{
    QStringList currentValues = d->metadatas.value(key);

    d->metadatas.insert(key, currentValues + values);
}

void dtkComposerNodeAbstractTransmitter::addMetaData(const QString& key, const QString& value)
{
    QStringList currentValues = d->metadatas.value(key);

    d->metadatas.insert(key, currentValues << value);
}

void dtkComposerNodeAbstractTransmitter::setMetaData(const QString& key, const QStringList& values)
{
    d->metadatas.insert(key, values);
}

void dtkComposerNodeAbstractTransmitter::setMetaData(const QString& key, const QString& value)
{
    d->metadatas.insert(key, QStringList() << value);
}

QStringList dtkComposerNodeAbstractTransmitter::metaDataList(void) const
{
    return d->metadatas.keys();
}

QStringList dtkComposerNodeAbstractTransmitter::metaDataValues(const QString& key) const
{
    if(d->metadatas.contains(key))
	return d->metadatas[key];

    return QStringList();
}

bool dtkComposerNodeAbstractTransmitter::hasMetaData(const QString& key) const
{
    return d->metadatas.contains(key);
}

QString dtkComposerNodeAbstractTransmitter::metadata(const QString& key) const
{
    if(!d->metadatas.contains(key)) {
	dtkDebug() << "Transmitter has no such metadata:" << key;
	return QString();
    }

    return d->metadatas.value(key).first();
}

QStringList dtkComposerNodeAbstractTransmitter::metadatas(const QString& key) const
{
    if(!d->metadatas.contains(key)) {
	dtkDebug() << "Transmitter has no such metadata:" << key;
	return QStringList();
    }

    return d->metadatas.value(key);
}


// /////////////////////////////////////////////////////////////////
// Debug operators
// /////////////////////////////////////////////////////////////////

//! Writes the transmitter's identifier to the stream.
/*! 
 *  
 */
QDebug operator<<(QDebug debug, const dtkComposerNodeAbstractTransmitter& transmitter)
{
    debug.nospace() << transmitter.identifier();
    
    return debug.space();
};

//!  Writes the transmitter's identifier to the stream.
/*! 
 *  
 */
QDebug operator<<(QDebug debug, dtkComposerNodeAbstractTransmitter *transmitter)
{
    debug.nospace() << transmitter->identifier();
    
    return debug.space();
};
