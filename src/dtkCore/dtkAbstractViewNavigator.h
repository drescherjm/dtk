/* dtkAbstractViewNavigator.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Jan 29 14:36:41 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Mon Sep  5 12:57:00 2011 (+0200)
 *           By: Julien Wintz
 *     Update #: 82
 */

/* Commentary:
 *
 */

/* Change log:
 *
 */

#ifndef DTKABSTRACTVIEWNAVIGATOR_H
#define DTKABSTRACTVIEWNAVIGATOR_H

#include <dtkCore/dtkAbstractObject.h>

class dtkAbstractViewNavigatorPrivate;

class dtkAbstractData;
class dtkAbstractView;

class DTKCORE_EXPORT dtkAbstractViewNavigator : public dtkAbstractObject
{
    Q_OBJECT

public:
             dtkAbstractViewNavigator(void);
    virtual ~dtkAbstractViewNavigator(void);

    virtual QString description(void) const = 0;
    virtual QStringList handled(void) const = 0;

            bool enabled(void) const;
    virtual void  enable(void);
    virtual void disable(void);

    virtual void setData(dtkAbstractData *data);
    virtual void setView(dtkAbstractView *view);

    virtual dtkAbstractData *data(void);
    virtual dtkAbstractView *view(void);

    virtual dtkAbstractData *output (void);
    virtual dtkAbstractData *output (int channel);
    virtual dtkAbstractData *output (int channel, int frame);

    virtual void  predraw(void) {}
    virtual void     draw(void) {}
    virtual void postdraw(void) {}

signals:
    void updated(void);

private:
    dtkAbstractViewNavigatorPrivate *d;
};

#endif
