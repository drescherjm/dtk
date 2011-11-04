/* dtkAbstractDataSerializer.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2011 - Nicolas Niclausse, Inria.
 * Created: lun. oct. 17 13:20:01 2011 (+0200)
 * Version: $Id$
 * Last-Updated: mer. oct. 19 12:47:17 2011 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 31
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKABSTRACTDATASERIALIZER_H
#define DTKABSTRACTDATASERIALIZER_H


#include <dtkCore/dtkAbstractObject.h>
#include <dtkCore/dtkAbstractData.h>

class dtkAbstractDataSerializerPrivate;

class DTKCORE_EXPORT dtkAbstractDataSerializer : public dtkAbstractObject
{
    Q_OBJECT

public:
             dtkAbstractDataSerializer(void);
    virtual ~dtkAbstractDataSerializer(void);

    virtual QStringList handled(void) const = 0;

    bool enabled(void) const;
    void enable(void);
    void disable(void);

    QByteArray *data(void);

signals:
    void started(const QString& message);
    void progressed(int step);
    void finished(void);

public slots:

    virtual bool canSerialize(const dtkAbstractData &data);
    virtual bool serialize(  dtkAbstractData &data);

    virtual void setProgress(int value);

protected:
    virtual void setData(QByteArray *array);


private:
    dtkAbstractDataSerializerPrivate *d;
};

#endif
