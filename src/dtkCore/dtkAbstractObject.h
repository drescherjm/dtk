/* dtkAbstractObject.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sat Feb 28 17:43:14 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Sat Aug  1 00:35:09 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 32
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
   ~dtkAbstractObject(void);

   void addProperty(QString key, QStringList values);
   void addProperty(QString key, QString value);
   void setProperty(QString key, QString value);
   const QStringList propertyValues(QString key);

   bool hasProperty(QString key);
   QString property(QString key);

signals:
   void propertySet(QString key, QString value);

public slots:
   virtual void onPropertySet(QString key, QString value);

private:
   dtkAbstractObjectPrivate *d;
};

#endif
