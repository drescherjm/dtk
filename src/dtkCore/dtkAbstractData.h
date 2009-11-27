/* dtkAbstractData.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Nov  7 16:00:26 2008 (+0100)
 * Version: $Id$
 * Last-Updated: Sat Nov 14 14:12:59 2009 (+0100)
 *           By: Julien Wintz
 *     Update #: 183
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKABSTRACTDATA_H
#define DTKABSTRACTDATA_H

#include <dtkCore/dtkAbstractObject.h>

class dtkAbstractDataReader;
class dtkAbstractDataWriter;
class dtkAbstractDataPrivate;

class DTKCORE_EXPORT dtkAbstractData : public dtkAbstractObject
{
    Q_OBJECT

public:
             dtkAbstractData(      dtkAbstractData *parent = 0);
             dtkAbstractData(const dtkAbstractData& data);
    virtual ~dtkAbstractData(void);

    virtual QString description(void) const;

    friend QDebug operator<<(QDebug debug, const dtkAbstractData& data);
    friend QDebug operator<<(QDebug debug,       dtkAbstractData *data);

    virtual void draw(void) {}

public slots:
    virtual bool read(QString file);
    virtual bool read(QStringList files);

    virtual bool write(QString file);
    virtual bool write(QStringList files);

    virtual void *output(void);

    virtual void *data(void);
    virtual void *data(int channel);

    virtual void setParameter(int parameter);
    virtual void setParameter(int parameter, int channel);

    virtual void setData(void* data);
    virtual void setData(void* data, int channel);

    virtual void update(void);

    void addReader(dtkAbstractDataReader *reader);
    void addWriter(dtkAbstractDataWriter *writer);

    void  enableReader(QString reader);
    void disableReader(QString reader);

    void  enableWriter(QString writer);
    void disableWriter(QString writer);

    dtkAbstractDataReader *reader(QString type);
    dtkAbstractDataWriter *writer(QString type);

    QString     path(void);
    QStringList paths(void);

    virtual       QImage & thumbnail(void)  const;
    virtual QList<QImage>& thumbnails(void) const;

private:
    dtkAbstractDataPrivate *d;
};

QDebug operator<<(QDebug debug, const dtkAbstractData& data);
QDebug operator<<(QDebug debug,       dtkAbstractData *data);

#endif
