/* dtkAbstractObject.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sat Feb 28 17:43:14 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Jun 30 19:26:32 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 85
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

   bool hasProperty(QString key);
   void addProperty(QString key, QStringList values);
   void addProperty(QString key, QString value);
   void setProperty(QString key, QString value);
   const QStringList propertyValues(QString key);
   QString property(QString key);

   bool hasMetaData(QString key);
   void addMetaData(QString key, QStringList values);
   void addMetaData(QString key, QString value);
   void setMetaData(QString key, QStringList values);
   void setMetaData(QString key, QString value);
   const QStringList metaDataValues(QString key);
   QString metadata(QString key);
   QStringList metadatas(QString key);
   
signals:
   void propertySet(QString key, QString value);
   void metaDataSet(QString key, QString value);

public slots:
   virtual void onPropertySet(QString key, QString value);
   virtual void onMetaDataSet(QString key, QString value);

private:
   dtkAbstractObjectPrivate *d;
};

#endif
