/* dtkAbstractDataDeserializer.h ---
 *
 * Author: Nicolas Niclausse
 * Copyright (C) 2011 - Nicolas Niclausse, Inria.
 * Created: lun. oct. 17 13:20:01 2011 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Apr 24 11:10:31 2012 (+0200)
 *           By: tkloczko
 *     Update #: 20
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKABSTRACTDATADESERIALIZER_H
#define DTKABSTRACTDATADESERIALIZER_H


#include "dtkAbstractObject.h"

class dtkAbstractData;
class dtkAbstractDataDeserializerPrivate;

// /////////////////////////////////////////////////////////////////
// dtkAbstractDataDeserializer interface
// /////////////////////////////////////////////////////////////////

class DTKCORE_EXPORT dtkAbstractDataDeserializer : public dtkAbstractObject
{
    Q_OBJECT

public:
             dtkAbstractDataDeserializer(void);
             dtkAbstractDataDeserializer(const dtkAbstractDataDeserializer& other);
    virtual ~dtkAbstractDataDeserializer(void);

public:
    virtual QStringList handled(void) const = 0;

    bool enabled(void) const;
    void enable(void);
    void disable(void);

    dtkAbstractData *data(void) const;
    virtual void setData(dtkAbstractData *data);

signals:
    void started(const QString& message);
    void progressed(int step);
    void finished(void);

public slots:
    virtual bool deserialize(const QByteArray& array);

    virtual void setProgress(int value);

private:
    DTK_DECLARE_PRIVATE(dtkAbstractDataDeserializer);
};

#endif
