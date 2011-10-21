/* dtkAbstractObject.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sat Feb 28 17:43:14 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Sep  5 12:58:36 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 112
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

   virtual QString description(void) const;
   virtual QString identifier(void) const;
   virtual QString name(void) const;

   int count(void) const;
   int retain(void) const;
   int release(void) const;

   void enableDeferredDeletion(bool value);
   bool     isDeferredDeletionEnabled(void) const;

   bool hasProperty(const QString& key) const;
   void addProperty(const QString& key, const QStringList& values);
   void addProperty(const QString& key, const QString& value);
   void setProperty(const QString& key, const QString& value);
   QStringList propertyList(void) const;
   QStringList propertyValues(const QString& key) const;
   QString property(const QString& key) const;

   bool hasMetaData(const QString& key) const;
   void addMetaData(const QString& key, const QStringList& values);
   void addMetaData(const QString& key, const QString& value);
   void setMetaData(const QString& key, const QStringList& values);
   void setMetaData(const QString& key, const QString& value);
   QStringList metaDataList(void) const;
   QStringList metaDataValues(const QString& key) const;
   QString metadata(const QString& key) const;
   QStringList metadatas(const QString& key) const;
   void copyMetaDataFrom(const dtkAbstractObject *obj);

signals:
   void propertySet(const QString& key, const QString& value);
   void metaDataSet(const QString& key, const QString& value);

public slots:
   virtual void onPropertySet(const QString& key, const QString& value);
   virtual void onMetaDataSet(const QString& key, const QString& value);

private:
   dtkAbstractObjectPrivate *d;
};

#endif
