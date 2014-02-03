/* dtkAbstractDataFactory.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Nov  7 15:48:10 2008 (+0100)
 * Version: $Id$
 * Last-Updated: lun. févr.  3 13:43:19 2014 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 144
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKABSTRACTDATAFACTORY_H
#define DTKABSTRACTDATAFACTORY_H

#include "dtkAbstractFactory.h"
#include <dtkCoreSupport/dtkSmartPointer>
#include <dtkCoreSupport/dtkAbstractData>
#include <dtkCoreSupport/dtkAbstractDataConverter>
#include <dtkCoreSupport/dtkAbstractDataReader>
#include <dtkCoreSupport/dtkAbstractDataWriter>
#include <dtkCoreSupport/dtkAbstractDataSerializer>
#include <dtkCoreSupport/dtkAbstractDataDeserializer>

class dtkAbstractData;
class dtkAbstractDataReader;
class dtkAbstractDataWriter;
class dtkAbstractDataConverter;
class dtkAbstractDataSerializer;
class dtkAbstractDataDeserializer;
class dtkAbstractDataFactoryPrivate;
template<class T> class dtkSmartPointer;

class DTKCORESUPPORT_EXPORT dtkAbstractDataFactory : public dtkAbstractFactory
{
    Q_OBJECT

public:
    typedef dtkAbstractData           *(*dtkAbstractDataCreator)         (void);
    typedef dtkAbstractDataReader     *(*dtkAbstractDataReaderCreator)   (void);
    typedef dtkAbstractDataWriter     *(*dtkAbstractDataWriterCreator)   (void);
    typedef dtkAbstractDataConverter  *(*dtkAbstractDataConverterCreator)(void);
    typedef dtkAbstractDataSerializer *(*dtkAbstractDataSerializerCreator)(void);
    typedef dtkAbstractDataDeserializer *(*dtkAbstractDataDeserializerCreator)(void);

public:
    typedef QMap<int, QString> dtkAbstractDataFactoryReaderPriorityMap;
    typedef QMap<int, QString> dtkAbstractDataFactoryWriterPriorityMap;
    typedef QMap<int, QString> dtkAbstractDataFactoryConverterPriorityMap;

public:
    static dtkAbstractDataFactory *instance(void);

    bool registerDataType         (const QString& type,                             dtkAbstractDataCreator          func);
    bool registerDataType         (const QString& type,                             dtkAbstractDataCreator          func, const QString& itf);
    bool registerDataReaderType   (const QString& type, const QStringList& handled, dtkAbstractDataReaderCreator    func);
    bool registerDataWriterType   (const QString& type, const QStringList& handled, dtkAbstractDataWriterCreator    func);
    bool registerDataConverterType(const QString& type, const QStringList& fromTypes, const QString& toType,  dtkAbstractDataConverterCreator func);
    bool registerDataSerializerType(const QString& type, const QStringList& handled, dtkAbstractDataSerializerCreator func);
    bool registerDataDeserializerType(const QString& type, const QStringList& handled, dtkAbstractDataDeserializerCreator func);

    unsigned int count(const QString& type) const;
    unsigned int countReaders      (const QString& type) const;
    unsigned int countWriters      (const QString& type) const;
    unsigned int countConverters   (const QString& type) const;
    unsigned int countSerializers  (const QString& type) const;
    unsigned int countDeserializers(const QString& type) const;

    QList<QString> creators(void) const;
    QList<QString> readers(void) const;
    QList<QString> writers(void) const;
    QList<QString> converters(void) const;
    QList<QString> serializers(void) const;
    QList<QString> deserializers(void) const;

public:
    void setReaderPriorities(const dtkAbstractDataFactoryReaderPriorityMap& priorities);
    void setWriterPriorities(const dtkAbstractDataFactoryWriterPriorityMap& priorities);
    void setConverterPriorities(const dtkAbstractDataFactoryConverterPriorityMap& priorities);

    const dtkAbstractDataFactoryReaderPriorityMap& readerPriorities(void) const;
    const dtkAbstractDataFactoryWriterPriorityMap& writerPriorities(void) const;
    const dtkAbstractDataFactoryConverterPriorityMap& converterPriorities(void) const;

public:
    QStringList implementations(void);
    QStringList implementations(const QString& intf);
    QStringList interfaces(void);

signals:
    void created(dtkAbstractData *data, const QString& type);

public slots:
    dtkAbstractData            *create   (const QString& type);
    dtkAbstractDataReader      *reader   (const QString& type);
    dtkAbstractDataWriter      *writer   (const QString& type);
    dtkAbstractDataConverter   *converter(const QString& type);
    dtkAbstractDataSerializer  *serializer(const QString& type);
    dtkAbstractDataDeserializer *deserializer(const QString& type);

    dtkSmartPointer<dtkAbstractData>          createSmartPointer   (const QString& type);
    dtkSmartPointer<dtkAbstractDataReader>    readerSmartPointer   (const QString& type);
    dtkSmartPointer<dtkAbstractDataWriter>    writerSmartPointer   (const QString& type);
    dtkSmartPointer<dtkAbstractDataConverter> converterSmartPointer(const QString& type);
    dtkSmartPointer<dtkAbstractDataSerializer> serializerSmartPointer(const QString& type);
    dtkSmartPointer<dtkAbstractDataDeserializer> deserializerSmartPointer(const QString& type);

protected:
     dtkAbstractDataFactory(void);
    ~dtkAbstractDataFactory(void);

private:
    static dtkAbstractDataFactory *s_instance;

private:
    dtkAbstractDataFactoryPrivate *d;
};

#endif
