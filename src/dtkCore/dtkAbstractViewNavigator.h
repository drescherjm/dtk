/* dtkAbstractViewNavigator.h ---
 *
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Thu Jan 29 14:36:41 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Jul 31 23:49:34 2009 (+0200)
 *           By: Julien Wintz
 *     Update #: 77
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

            bool enabled(void);
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

public slots:
    virtual void    updatePosition(          double x, double y, double z) {} // -- to be moved later on
    virtual void updateOrientation(double a, double x, double y, double z) {} // -- to be moved later on

    virtual void update(double tx, double ty, double tz) {}                                  // -- to be moved later on
    virtual void update(double tx, double ty, double tz, double rx, double ry, double rz) {} // -- to be moved later on

    virtual void update(double thumb, double index, double middle, double ring, double pinky) {} // -- to be moved later on

private:
    dtkAbstractViewNavigatorPrivate *d;
};

#endif
