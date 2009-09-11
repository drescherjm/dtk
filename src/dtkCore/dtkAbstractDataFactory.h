/* dtkAbstractDataFactory.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Nov  7 15:48:10 2008 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Sep 11 13:28:16 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 62
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
class dtkAbstractDataFactoryPrivate;

class DTKCORE_EXPORT dtkAbstractDataFactory : public dtkAbstractFactory
{
    Q_OBJECT

public:
    typedef dtkAbstractData       *(*dtkAbstractDataCreator)      (void);
    typedef dtkAbstractDataReader *(*dtkAbstractDataReaderCreator)(void);
    typedef dtkAbstractDataWriter *(*dtkAbstractDataWriterCreator)(void);

    typedef QHash<               QString,      dtkAbstractDataCreator>       dtkAbstractDataCreatorHash;
    typedef QHash<QPair<QString, QStringList>, dtkAbstractDataReaderCreator> dtkAbstractDataReaderCreatorHash;
    typedef QHash<QPair<QString, QStringList>, dtkAbstractDataWriterCreator> dtkAbstractDataWriterCreatorHash;

    typedef       QPair<QString, QStringList>  dtkAbstractDataTypeHandler;

public:
    static dtkAbstractDataFactory *instance(void);

    bool registerDataType      (QString type,                      dtkAbstractDataCreator       func);
    bool registerDataReaderType(QString type, QStringList handled, dtkAbstractDataReaderCreator func);
    bool registerDataWriterType(QString type, QStringList handled, dtkAbstractDataWriterCreator func);

    unsigned int size(QString type);

    dtkAbstractData *get(QString type, int index = 0);
    dtkAbstractData *get(QString type, QString name);

signals:
    void created(dtkAbstractData *data, QString type);

public slots:
    dtkAbstractData *create(QString type);

protected:
     dtkAbstractDataFactory(void);
    ~dtkAbstractDataFactory(void);

private:
    static dtkAbstractDataFactory *s_instance;

private:
    dtkAbstractDataFactoryPrivate *d;
};

#endif
