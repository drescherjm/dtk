/* dtkAbstractDataReader.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Feb 24 21:58:48 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Jul 31 23:13:25 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 26
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
   ~dtkAbstractDataReader(void);

   virtual QString description(void) const = 0;
   virtual QStringList handled(void) const = 0;

   bool enabled(void);
   void  enable(void);
   void disable(void);

   dtkAbstractData *data(void);

   virtual void setData(dtkAbstractData *data);

public slots:
   virtual bool read(const QString& path);

private:
   dtkAbstractDataReaderPrivate *d;
};

#endif
