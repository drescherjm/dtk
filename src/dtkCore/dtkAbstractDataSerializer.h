/* dtkAbstractDataSerializer.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2011 - Nicolas Niclausse, Inria.
 * Created: lun. oct. 17 13:20:01 2011 (+0200)
 * Version: $Id$
 * Last-Updated: lun. nov. 28 15:26:02 2011 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 37
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKABSTRACTDATASERIALIZER_H
#define DTKABSTRACTDATASERIALIZER_H


#include "dtkAbstractObject.h"
#include "dtkAbstractData.h"

class dtkAbstractData;
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

    virtual QByteArray *serialize(  void );
    virtual QByteArray *serialize(  dtkAbstractData *data);

    virtual void setProgress(int value);

protected:
    virtual void setData(QByteArray *array);


private:
    dtkAbstractDataSerializerPrivate *d;
};

#endif
