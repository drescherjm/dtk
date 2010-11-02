/* dtkAbstractDataFactory.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Nov  7 15:48:10 2008 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Oct 31 19:47:10 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 81
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKABSTRACTDATAFACTORY_H
#define DTKABSTRACTDATAFACTORY_H

#include <dtkCore/dtkAbstractFactory.h>

class dtkAbstractData;
class dtkAbstractDataReader;
class dtkAbstractDataWriter;
class dtkAbstractDataConverter;
class dtkAbstractDataFactoryPrivate;

class DTKCORE_EXPORT dtkAbstractDataFactory : public dtkAbstractFactory
{
    Q_OBJECT

public:
    typedef dtkAbstractData          *(*dtkAbstractDataCreator)         (void);
    typedef dtkAbstractDataReader    *(*dtkAbstractDataReaderCreator)   (void);
    typedef dtkAbstractDataWriter    *(*dtkAbstractDataWriterCreator)   (void);
    typedef dtkAbstractDataConverter *(*dtkAbstractDataConverterCreator)(void);

    typedef QHash<               QString,      dtkAbstractDataCreator>          dtkAbstractDataCreatorHash;
    typedef QHash<QPair<QString, QStringList>, dtkAbstractDataReaderCreator>    dtkAbstractDataReaderCreatorHash;
    typedef QHash<QPair<QString, QStringList>, dtkAbstractDataWriterCreator>    dtkAbstractDataWriterCreatorHash;
    typedef QHash<QPair<QString, QPair<QStringList, QString> >, dtkAbstractDataConverterCreator> dtkAbstractDataConverterCreatorHash;
    typedef       QPair<QString, QStringList>  dtkAbstractDataTypeHandler;
    typedef       QPair<QString, QPair<QStringList, QString> >  dtkAbstractDataConverterTypeHandler;

public:
    static dtkAbstractDataFactory *instance(void);

    bool registerDataType         (QString type,                      dtkAbstractDataCreator          func);
    bool registerDataReaderType   (QString type, QStringList handled, dtkAbstractDataReaderCreator    func);
    bool registerDataWriterType   (QString type, QStringList handled, dtkAbstractDataWriterCreator    func);
    bool registerDataConverterType(QString type, QStringList fromTypes, QString toType,  dtkAbstractDataConverterCreator func);

    unsigned int size(QString type);

    unsigned int count(QString type);
    unsigned int countReaders   (QString type);
    unsigned int countWriters   (QString type);
    unsigned int countConverters(QString type);

    dtkAbstractData *get(QString type, int index = 0);
    dtkAbstractData *get(QString type, QString name);

    QList<dtkAbstractDataTypeHandler>          readers(void);
    QList<dtkAbstractDataTypeHandler>          writers(void);
    QList<dtkAbstractDataConverterTypeHandler> converters(void);

signals:
    void created(dtkAbstractData *data, QString type);

public slots:
    dtkAbstractData          *create   (QString type);
    dtkAbstractDataReader    *reader   (QString type, QStringList handled);
    dtkAbstractDataWriter    *writer   (QString type, QStringList handled);
    dtkAbstractDataConverter *converter(QString type, QStringList fromType, QString toType);

protected:
     dtkAbstractDataFactory(void);
    ~dtkAbstractDataFactory(void);

private:
    static dtkAbstractDataFactory *s_instance;

private:
    dtkAbstractDataFactoryPrivate *d;
};

#endif
