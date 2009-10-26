/* dtkAbstractDataReader.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Tue Feb 24 21:58:48 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Oct 26 12:06:07 2009 (+0100)
 *           By: Julien Wintz
 *     Update #: 39
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

signals:
   void started(const QString& message);
   void progressed(int step);
   void finished(void);

public slots:
   virtual bool canRead(QString file);
   virtual bool canRead(QStringList files);

   virtual bool read(QString file);
   virtual bool read(QStringList files);

   virtual void readInformation(QString path);
   virtual void readInformation(QStringList paths);

private:
   dtkAbstractDataReaderPrivate *d;
};

#endif
