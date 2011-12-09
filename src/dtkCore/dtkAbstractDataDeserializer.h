/* dtkAbstractDataDeserializer.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2011 - Nicolas Niclausse, Inria.
 * Created: lun. oct. 17 13:20:01 2011 (+0200)
 * Version: $Id$
 * Last-Updated: lun. nov. 28 15:54:40 2011 (+0100)
 *           By: Nicolas Niclausse
 *     Update #: 11
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKABSTRACTDATADESERIALIZER_H
#define DTKABSTRACTDATADESERIALIZER_H


#include <dtkCore/dtkAbstractObject.h>
#include <dtkCore/dtkAbstractData.h>

class dtkAbstractDataDeserializerPrivate;

class DTKCORE_EXPORT dtkAbstractDataDeserializer : public dtkAbstractObject
{
    Q_OBJECT

public:
             dtkAbstractDataDeserializer(void);
    virtual ~dtkAbstractDataDeserializer(void);

    virtual QStringList handled(void) const = 0;

    bool enabled(void) const;
    void enable(void);
    void disable(void);

    dtkAbstractData *data(void);
    virtual void setData(dtkAbstractData *data);

signals:
    void started(const QString& message);
    void progressed(int step);
    void finished(void);

public slots:

    virtual bool deserialize(QByteArray *array);

    virtual void setProgress(int value);

private:
    dtkAbstractDataDeserializerPrivate *d;
};

#endif
