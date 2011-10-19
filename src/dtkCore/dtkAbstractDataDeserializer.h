/* dtkAbstractDataDeserializer.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2011 - Nicolas Niclausse, Inria.
 * Created: lun. oct. 17 13:20:01 2011 (+0200)
 * Version: $Id$
 * Last-Updated: mer. oct. 19 12:46:59 2011 (+0200)
 *           By: Nicolas Niclausse
 *     Update #: 4
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

signals:
    void started(const QString& message);
    void progressed(int step);
    void finished(void);

public slots:
    virtual bool canDeserialize(const QByteArray& binary);

    virtual bool deserialize(const QByteArray& binary);

    virtual void setProgress(int value);

protected:
    virtual void setData(dtkAbstractData *data);

private:
    dtkAbstractDataDeserializerPrivate *d;
};

#endif
