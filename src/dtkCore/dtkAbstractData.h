/* dtkAbstractData.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Nov  7 16:00:26 2008 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Sep 15 15:09:33 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 202
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

#include <QtGui/QImage>

class dtkAbstractDataReader;
class dtkAbstractDataWriter;
class dtkAbstractDataConverter;
class dtkAbstractDataPrivate;

class DTKCORE_EXPORT dtkAbstractData : public dtkAbstractObject
{
    Q_OBJECT

public:
             dtkAbstractData(      dtkAbstractData *parent = 0);
             dtkAbstractData(const dtkAbstractData& data);
    virtual ~dtkAbstractData(void);

    friend DTKCORE_EXPORT QDebug operator<<(QDebug debug, const dtkAbstractData& data);
    friend DTKCORE_EXPORT QDebug operator<<(QDebug debug,       dtkAbstractData *data);

    virtual void draw(void) {}

public slots:
    virtual bool read(const QString& file);
    virtual bool read(const QStringList& files);

    virtual bool write(const QString& file);
    virtual bool write(const QStringList& files);

    virtual dtkAbstractData *convert(const QString& toType);

    virtual void *output(void);
    virtual void *output(int channel);

    virtual void *data(void);
    virtual void *data(int channel);

    virtual double parameter(int channel);

    virtual int numberOfChannels(void);

    virtual void setParameter(int parameter);
    virtual void setParameter(int parameter, int channel);

    virtual void setParameter(float parameter);
    virtual void setParameter(float parameter, int channel);

    virtual void setParameter(double parameter);
    virtual void setParameter(double parameter, int channel);

    virtual void setParameter(const QString& parameter);
    virtual void setParameter(const QString& parameter, int channel);

    virtual void setParameter(dtkAbstractData *parameter);
    virtual void setParameter(dtkAbstractData *parameter, int channel);

    virtual void setData(void* data);
    virtual void setData(void* data, int channel);

    virtual void setNumberOfChannels(int number);
    
    virtual void update(void);

    void addReader   (const QString& reader);
    void addWriter   (const QString& writer);
    void addConverter(const QString& converter);

    void  enableReader(const QString& reader);
    void disableReader(const QString& reader);

    void  enableWriter(const QString& writer);
    void disableWriter(const QString& writer);

    void  enableConverter(const QString& converter);
    void disableConverter(const QString& converter);

    dtkAbstractDataReader    *reader   (const QString& type);
    dtkAbstractDataWriter    *writer   (const QString& type);
    dtkAbstractDataConverter *converter(const QString& type);

    QString     path(void);
    QStringList paths(void);

    virtual       QImage & thumbnail(void)  const;
    virtual QList<QImage>& thumbnails(void) const;

public:
    virtual bool casts(const QString& type);

    virtual operator bool   (void);
    virtual operator int    (void);
    virtual operator float  (void);
    virtual operator double (void);

private:
    dtkAbstractDataPrivate *d;
};

DTKCORE_EXPORT QDebug operator<<(QDebug debug, const dtkAbstractData& data);
DTKCORE_EXPORT QDebug operator<<(QDebug debug,       dtkAbstractData *data);

Q_DECLARE_METATYPE(dtkAbstractData)

#endif
