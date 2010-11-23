/* dtkAbstractDataConverter.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Feb 24 21:58:48 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Sun Oct 31 19:45:27 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 45
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKABSTRACTDATACONVERTER_H
#define DTKABSTRACTDATACONVERTER_H

#include <dtkCore/dtkAbstractObject.h>

class dtkAbstractData;
class dtkAbstractDataConverterPrivate;

class DTKCORE_EXPORT dtkAbstractDataConverter : public dtkAbstractObject
{
    Q_OBJECT

public:
             dtkAbstractDataConverter(void);
    virtual ~dtkAbstractDataConverter(void);
    
    virtual QString  description (void) const = 0;
    virtual QStringList fromTypes(void) const = 0;
    virtual QString       toType (void) const = 0;
    
    bool enabled(void) const;
    void  enable(void);
    void disable(void);
    
    dtkAbstractData *data(void);
    
    virtual void setData(dtkAbstractData *data);

signals:
    void started(const QString & message);
    void progressed(int step);
    void finished(void);
    
public slots:
    virtual bool canConvert(const QString & toType);
    
    virtual dtkAbstractData *convert(void);
    
    virtual void setProgress(int value);
    
private:
    dtkAbstractDataConverterPrivate *d;
};

#endif
