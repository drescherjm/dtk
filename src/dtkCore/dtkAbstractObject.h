/* dtkAbstractObject.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sat Feb 28 17:43:14 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Tue Jul  6 21:02:55 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 91
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKABSTRACTOBJECT_H
#define DTKABSTRACTOBJECT_H

#include <dtkCore/dtkCoreExport.h>
#include <dtkCore/dtkGlobal.h>

class dtkAbstractObjectPrivate;

class DTKCORE_EXPORT dtkAbstractObject : public QObject
{
    Q_OBJECT

public:
            dtkAbstractObject(dtkAbstractObject *parent = 0);
   virtual ~dtkAbstractObject(void);

   QString name(void) const;

   int count(void);
   int retain(void);
   int release(void);

   bool hasProperty(const QString & key) const;
   void addProperty(const QString & key, const QStringList & values);
   void addProperty(const QString & key, const QString & value);
   void setProperty(const QString & key, const QString & value);
   QStringList propertyValues(const QString & key) const;
   QString property(const QString & key) const;

   bool hasMetaData(const QString & key) const;
   void addMetaData(const QString & key, const QStringList & values);
   void addMetaData(const QString & key, const QString & value);
   void setMetaData(const QString & key, const QStringList & values);
   void setMetaData(const QString & key, const QString & value);
   QStringList metaDataValues(const QString & key) const;
   QString metadata(const QString & key) const;
   QStringList metadatas(const QString & key) const;

signals:
   void propertySet(const QString & key, const QString & value);
   void metaDataSet(const QString & key, const QString & value);

public slots:
   virtual void onPropertySet(const QString & key, const QString & value);
   virtual void onMetaDataSet(const QString & key, const QString & value);

private:
   dtkAbstractObjectPrivate *d;
};

#endif
