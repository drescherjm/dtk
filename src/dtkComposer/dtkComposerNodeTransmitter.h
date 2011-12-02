/* dtkComposerNodeTransmitter.h --- 
 * 
 * Author: Thibaud Kloczko
 * Copyright (C) 2011 - Thibaud Kloczko, Inria.
 * Created: Wed Nov  2 09:44:16 2011 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Nov 28 14:36:50 2011 (+0100)
 *           By: Julien Wintz
 *     Update #: 56
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKCOMPOSERNODETRANSMITTER_H
#define DTKCOMPOSERNODETRANSMITTER_H

#include "dtkComposerExport.h"

#include <dtkCore/dtkLog>

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeAbstractTransmitter declaration
// /////////////////////////////////////////////////////////////////

#include <dtkCore/dtkGlobal>

class QDebug;
class QString;

class dtkComposerNodeAbstractTransmitterPrivate;

class DTKCOMPOSER_EXPORT dtkComposerNodeAbstractTransmitter
{
public:
             dtkComposerNodeAbstractTransmitter(void);
    virtual ~dtkComposerNodeAbstractTransmitter(void);

public:
    virtual void setCurrentData(dtkxarch_int index) = 0;

    virtual void clear(void) = 0;

    virtual QString identifier(void) const = 0;

public:
    void addMetaData(const QString& key, const QStringList& values);
    void addMetaData(const QString& key, const QString& value);
    void setMetaData(const QString& key, const QStringList& values);
    void setMetaData(const QString& key, const QString& value);

    bool hasMetaData(const QString& key) const;

    QStringList metaDataList(void) const;
    QStringList metaDataValues(const QString& key) const;
    QString metadata(const QString& key) const;
    QStringList metadatas(const QString& key) const;
    
public:
    friend DTKCOMPOSER_EXPORT QDebug operator<<(QDebug debug, const dtkComposerNodeAbstractTransmitter& transmitter);
    friend DTKCOMPOSER_EXPORT QDebug operator<<(QDebug debug,       dtkComposerNodeAbstractTransmitter *transmitter);

private:
    dtkComposerNodeAbstractTransmitterPrivate *d;
};

// /////////////////////////////////////////////////////////////////
// Debug operators
// /////////////////////////////////////////////////////////////////

DTKCOMPOSER_EXPORT QDebug operator<<(QDebug debug, const dtkComposerNodeAbstractTransmitter& transmitter);
DTKCOMPOSER_EXPORT QDebug operator<<(QDebug debug,       dtkComposerNodeAbstractTransmitter *transmitter);

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeTransmitter declaration
// /////////////////////////////////////////////////////////////////

template <typename T> class QVector;
template <typename T> class QList;

template <typename T> class DTKCOMPOSER_EXPORT dtkComposerNodeTransmitter : public dtkComposerNodeAbstractTransmitter
{
public:
     dtkComposerNodeTransmitter(void);
    ~dtkComposerNodeTransmitter(void);

public:
    inline void setData(const T& data);

    inline       T& data(void);
    inline const T& data(void) const;

public:
    void setVector(QVector<T> *vector);
    void   setList(  QList<T> *list);

public:
    QVector<T> *vector(void);
      QList<T> *list(void);

public:
    void setCurrentData(dtkxarch_int index);

public:
    void clear(void);

public:
    QString identifier(void) const;

private:
            T   m_data;
    QVector<T> *m_vector;
      QList<T> *m_list;
};

// /////////////////////////////////////////////////////////////////
// dtkComposerNodeTransmitter implementation
// /////////////////////////////////////////////////////////////////

#include "dtkComposerNodeTransmitter.tpp"

#endif
