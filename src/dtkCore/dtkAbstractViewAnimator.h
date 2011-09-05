/* dtkAbstractViewAnimator.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Jan 30 16:13:08 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Sep  5 12:56:40 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 28
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef DTKABSTRACTVIEWANIMATOR_H
#define DTKABSTRACTVIEWANIMATOR_H

#include <dtkCore/dtkAbstractObject.h>

class dtkAbstractData;
class dtkAbstractView;
class dtkAbstractViewAnimatorPrivate;

class DTKCORE_EXPORT dtkAbstractViewAnimator : public dtkAbstractObject
{
    Q_OBJECT

public:
    dtkAbstractViewAnimator(void);
   ~dtkAbstractViewAnimator(void);

   virtual QString description(void) const = 0;
   virtual QStringList handled(void) const = 0;
   
   dtkAbstractData *data(void);
   dtkAbstractView *view(void);

   virtual void setData(dtkAbstractData *data);
   virtual void setView(dtkAbstractView *view);

   bool enabled(void) const;
   void  enable(void);
   void disable(void);

public slots:
   virtual void start(void);
   virtual void  stop(void);

private:
   dtkAbstractViewAnimatorPrivate *d;
};

#endif
