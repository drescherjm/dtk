/* dtkAbstractDataWriter.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Feb 24 21:58:48 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Jul 21 09:14:25 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 34
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKABSTRACTDATAWRITER_H
#define DTKABSTRACTDATAWRITER_H

#include <dtkCore/dtkAbstractObject.h>

class dtkAbstractData;
class dtkAbstractDataWriterPrivate;

class DTKCORE_EXPORT dtkAbstractDataWriter : public dtkAbstractObject
{
    Q_OBJECT

public:
             dtkAbstractDataWriter(void);
    virtual ~dtkAbstractDataWriter(void);

    virtual QString description(void) const = 0;
    virtual QStringList handled(void) const = 0;
    
    bool enabled(void) const;
    void  enable(void);
    void disable(void);
    
    dtkAbstractData *data(void);
    
    virtual void setData(dtkAbstractData *data);
    
    /** Get the extension this writer prefers. 
        The list may depend on the data set by setData.
        The default implementation returns an empty StringList, 
        indicating no preferred extension.
      */
    virtual QStringList supportedFileExtensions () const;

signals:
    void started(const QString& message);
    void progressed(int step);
    void finished(void);

public slots:
    virtual bool canWrite(const QString& file);
    virtual bool canWrite(const QStringList& files);
    
    virtual bool write(const QString& file);
    virtual bool write(const QStringList& files);
    
    virtual void setProgress(int value);

private:
    dtkAbstractDataWriterPrivate *d;
};

#endif
