/* dtkAbstractDataFactory.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Nov  7 15:48:10 2008 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Oct  6 10:47:37 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 92
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
template<class T> class dtkSmartPointer;

class DTKCORE_EXPORT dtkAbstractDataFactory : public dtkAbstractFactory
{
    Q_OBJECT

public:
    typedef dtkAbstractData          *(*dtkAbstractDataCreator)         (void);
    typedef dtkAbstractDataReader    *(*dtkAbstractDataReaderCreator)   (void);
    typedef dtkAbstractDataWriter    *(*dtkAbstractDataWriterCreator)   (void);
    typedef dtkAbstractDataConverter *(*dtkAbstractDataConverterCreator)(void);

public:
    static dtkAbstractDataFactory *instance(void);

    bool registerDataType         (const QString& type,                             dtkAbstractDataCreator          func);
    bool registerDataType         (const QString& type,                             dtkAbstractDataCreator          func, const QString& interface);
    bool registerDataReaderType   (const QString& type, const QStringList& handled, dtkAbstractDataReaderCreator    func);
    bool registerDataWriterType   (const QString& type, const QStringList& handled, dtkAbstractDataWriterCreator    func);
    bool registerDataConverterType(const QString& type, const QStringList& fromTypes, const QString& toType,  dtkAbstractDataConverterCreator func);

    unsigned int count(const QString& type) const;
    unsigned int countReaders   (const QString& type) const;
    unsigned int countWriters   (const QString& type) const;
    unsigned int countConverters(const QString& type) const;

    QList<QString> creators(void) const;
    QList<QString> readers(void) const;
    QList<QString> writers(void) const;
    QList<QString> converters(void) const;

    dtkSmartPointer<dtkAbstractData>          createSmartPointer   (const QString& type);
    dtkSmartPointer<dtkAbstractDataReader>    readerSmartPointer   (const QString& type);
    dtkSmartPointer<dtkAbstractDataWriter>    writerSmartPointer   (const QString& type);
    dtkSmartPointer<dtkAbstractDataConverter> converterSmartPointer(const QString& type);

public:
    QStringList implementations(const QString& interface);
    QStringList interfaces(void);

signals:
    void created(dtkAbstractData *data, const QString& type);

public slots:
    dtkAbstractData          *create   (const QString& type);
    dtkAbstractDataReader    *reader   (const QString& type);
    dtkAbstractDataWriter    *writer   (const QString& type);
    dtkAbstractDataConverter *converter(const QString& type);

protected:
     dtkAbstractDataFactory(void);
    ~dtkAbstractDataFactory(void);

private:
    static dtkAbstractDataFactory *s_instance;

private:
    dtkAbstractDataFactoryPrivate *d;
};

#endif
