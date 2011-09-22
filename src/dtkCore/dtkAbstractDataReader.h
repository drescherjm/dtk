/* dtkAbstractDataReader.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Feb 24 21:58:48 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Sep 21 12:53:26 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 47
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKABSTRACTDATAREADER_H
#define DTKABSTRACTDATAREADER_H

#include <dtkCore/dtkAbstractObject.h>

class dtkAbstractData;
class dtkAbstractDataReaderPrivate;

class DTKCORE_EXPORT dtkAbstractDataReader : public dtkAbstractObject
{
    Q_OBJECT

public:
             dtkAbstractDataReader(void);
    virtual ~dtkAbstractDataReader(void);
    
    virtual QString description(void) const = 0;
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
    virtual bool canRead(const QString& file);
    virtual bool canRead(const QStringList& files);
    
    virtual bool read(const QString& file);
    virtual bool read(const QStringList& files);
    
    virtual void readInformation(const QString& path);
    virtual void readInformation(const QStringList& paths);
    
    virtual void setProgress(int value);

protected:
    const QString&     file(void);
    const QStringList& files(void);
    
private:
    dtkAbstractDataReaderPrivate *d;
};

#endif
