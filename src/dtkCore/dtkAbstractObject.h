/* dtkAbstractObject.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sat Feb 28 17:43:14 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Oct  5 14:33:42 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 63
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
class dtkComposerNode;
class dtkUi;

class DTKCORE_EXPORT dtkAbstractObject : public QObject
{
    Q_OBJECT

public:
    dtkAbstractObject(dtkAbstractObject *parent = 0);
   ~dtkAbstractObject(void);

   QString name(void) const;

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
   
   virtual dtkComposerNode *node(void) { 
       return NULL;
   }

   virtual dtkUi *ui(void) {
       return NULL;
   }

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
