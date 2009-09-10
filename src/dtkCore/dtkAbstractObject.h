/* dtkAbstractObject.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sat Feb 28 17:43:14 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Thu Sep 10 10:48:55 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 49
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

   void addProperty(QString key, QStringList values);
   void addProperty(QString key, QString value);
   void setProperty(QString key, QString value);
   const QStringList propertyValues(QString key);

   bool hasProperty(QString key);
   QString property(QString key);

   QString name(void) const;
   
   virtual dtkComposerNode *node(void) { 
       return NULL;
   }

   virtual dtkUi *ui(void) {
       return NULL;
   }

signals:
   void propertySet(QString key, QString value);

public slots:
   virtual void onPropertySet(QString key, QString value);

private:
   dtkAbstractObjectPrivate *d;
};

#endif
